#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include "OLED_Grafix.h"

#include <math.h>
#include "stdlib.h"

using namespace std;

OLED_Driver oled_d = OLED_Driver();

OLED_Grafix::OLED_Grafix(void){}

void OLED_Grafix::setGaugeText(bool text) {
    text_status = text;
}

void OLED_Grafix::setBarColor(uint16_t color = WHITE) {
    bar_color = color;
}

void OLED_Grafix::setGraphColor(uint16_t color = WHITE) {
    graph_color = color;
}

void OLED_Grafix::setTextColor(uint16_t color = WHITE) {
    text_color = color;
}

void OLED_Grafix::initScreen(void)
{
    Device_Init();
}

void OLED_Grafix::HBarGraph(int x, int y, float w, int h, float value, float maxi) 
{
    int pos = round((w / maxi) * value);
    oled_d.Set_Color(graph_color);
    drawRect(x, y, w, h);
    if (pos > w)
    {
        return;
    }
    if (pos < w - 2)
    {
        oled_d.Set_FillColor(bar_color);
        drawFRect(x + 1, y + 1, pos + 1, h - 2);
        oled_d.Set_FillColor(BLACK);
        drawFRect(x + pos + 2, y + 1, w - pos - 3, h - 2);
    }
    if (pos >= w - 2)
    {
        oled_d.Set_FillColor(bar_color);
        drawFRect(x + 2, y + 1, w - 3, h - 2);
    }
}

void OLED_Grafix::VBarGraph(int x, int y, int w, float h, float value, float maxi) {
    int pos = round((h / maxi) * value);
    if (pos > h)
    {
        return;
    }
    oled_d.Set_Color(graph_color);
    drawRect(x, y, w, h);
    if (pos < h - 2)
    {
        oled_d.Set_FillColor(bar_color);
        drawFRect(x + 1, (y + h) - pos - 1, w - 2, pos);
        oled_d.Set_FillColor(BLACK);
        drawFRect(x + 1, y + 1, w - 2,h - pos - 3);
    }
    if(pos >= h - 2)
    {
        oled_d.Set_FillColor(bar_color);
        drawFRect(x + 1, y + 1, w - 2, h - 2);
    }
}

void OLED_Grafix::drawRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
    Draw_FastHLine(x, y, w);
    Draw_FastHLine(x, y + h - 1, w);
    Draw_FastVLine(x, y, h);
    Draw_FastVLine(x + w - 1, y, h);
}

void OLED_Grafix::drawFRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
        return;

    // Y bounds check
    if (y + h > SSD1351_HEIGHT)
    {
        h = SSD1351_HEIGHT - y - 1;
    }

    // X bounds check
    if (x + w > SSD1351_WIDTH)
    {
        w = SSD1351_WIDTH - x - 1;
    }

    // set location
    Write_Command(SSD1351_CMD_SETCOLUMN);
    Write_Data(x);
    Write_Data(x + w - 1);
    Write_Command(SSD1351_CMD_SETROW);
    Write_Data(y);
    Write_Data(y + h - 1);

    // fill!
    Write_Command(SSD1351_CMD_WRITERAM);
    for (uint16_t i = 0; i < w * h; i++)
    {
        Write_Data(color_fill_byte[0]);
        Write_Data(color_fill_byte[1]);
    }
}

void OLED_Grafix::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    // Update in subclasses if desired!
    if (x0 == x1)
    {
        if (y0 > y1)
            swap(y0, y1);
        Draw_FastVLine(x0, y0, y1 - y0 + 1);
    }
    else if (y0 == y1)
    {
        if (x0 > x1)
            swap(x0, x1);
        Draw_FastHLine(x0, y0, x1 - x0 + 1);
    }
    else
        writeLine(x0, y0, x1, y1);
}

void OLED_Grafix::drawCircle(int16_t x0, int16_t y0, int16_t r)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    Draw_Pixel(x0, y0 + r);
    Draw_Pixel(x0, y0 - r);
    Draw_Pixel(x0 + r, y0);
    Draw_Pixel(x0 - r, y0);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        Draw_Pixel(x0 + x, y0 + y);
        Draw_Pixel(x0 - x, y0 + y);
        Draw_Pixel(x0 + x, y0 - y);
        Draw_Pixel(x0 - x, y0 - y);
        Draw_Pixel(x0 + y, y0 + x);
        Draw_Pixel(x0 - y, y0 + x);
        Draw_Pixel(x0 + y, y0 - x);
        Draw_Pixel(x0 - y, y0 - x);
    }
}

void OLED_Grafix::drawFCircle(int16_t x0, int16_t y0, int16_t r)
{
    Draw_FastVLine(x0, y0 - r, 2 * r + 1);
    FCircleHelper(x0, y0, r, 3, 0);
}

void OLED_Grafix::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    drawLine(x0, y0, x1, y1);
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x0, y0);
}

void OLED_Grafix::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r) 
{
    Draw_FastHLine(x + r, y, w - 2 * r);         // Top
    Draw_FastHLine(x + r, y + h - 1, w - 2 * r); // Bottom
    Draw_FastVLine(x, y + r, h - 2 * r);         // Left
    Draw_FastVLine(x + w - 1, y + r, h - 2 * r); // Right
    // draw four corners
    circleHelper(x + r, y + r, r, 1);
    circleHelper(x + w - r - 1, y + r, r, 2);
    circleHelper(x + w - r - 1, y + h - r - 1, r, 4);
    circleHelper(x + r, y + h - r - 1, r, 8);
}

void OLED_Grafix::drawGauge(uint16_t x0, uint16_t y0, uint16_t value, uint16_t maxi, uint16_t r)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    setColor(graph_color);
    Draw_Pixel(x0, y0 - r);
    Draw_Pixel(x0 + r, y0);
    Draw_Pixel(x0 - r, y0);
    Draw_FastHLine(x0-r,y0,r+r);
    
    if(value <= maxi && value >= 0) 
    { 
        setColor(bar_color);
        drawLine(x0, y0, x0 - (r - 1) * cos(value * (PI / maxi)), y0 - (r - 1) * sin(value * (PI / maxi)));
        setColor(BLACK);
        drawLine(x0, y0, x0 - (r - 1) * cos((value - 2) * (PI / maxi)), y0 - (r - 1) * sin((value - 2) * (PI / maxi)));

        drawLine(x0, y0, x0 - (r - 1) * cos((value + 2) * (PI / maxi)), y0 - (r - 1) * sin((value + 2) * (PI / maxi)));
        setColor(graph_color);
    }

    if(text_status) 
    {
        writeNumber(x0 - 5, y0 - 8, value);
    }

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        Draw_Pixel(x0 + x, y0 - y);
        Draw_Pixel(x0 - x, y0 - y);
        Draw_Pixel(x0 + y, y0 - x);
        Draw_Pixel(x0 - y, y0 - x);
    }
    
}

void OLED_Grafix::setColor(const uint8_t *text)
{
    Set_Color(text);
}

void OLED_Grafix::setFillColor(const uint8_t *text)
{
    Set_FillColor(text);
}

void OLED_Grafix::writeNumber(uint8_t x, uint8_t y, uint8_t num)
{
    oled_d.Set_Color(text_color);
    const char *nums[11] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    if(num<=9)
    {
        writeText(x, y, nums[num]);
        writeText(x + 6, y, " ");
        writeText(x + 12, y, " ");
    }
    if(num > 9)
    {
        writeText(x, y, nums[num / 10 % 10]);
        writeText(x + 6, y, nums[num % 10]);
        writeText(x + 12, y, " ");
    }
    if(num > 99)
    {
        writeText(x, y, nums[num / 100 % 10]);
        writeText(x + 6, y, nums[num / 10 % 10]);
        writeText(x + 12, y, nums[num % 10]);
    }
}

void OLED_Grafix::writeText(uint8_t x, uint8_t y, const uint8_t *text)
{
    uint8_t i = 0, j, k;
    oled_d.Set_Color(text_color);

    while (text[i] > 0x00)
    {
        if ((text[i] >= 0x20) && (text[i] <= 0x7e))
        {
            j = text[i] - 0x20;
            for (k = 0; k < 5; k++)
            {
                Set_Address(x + k, y);
                Write_text(ascii_table_5x8[j][k]);
            }
            Set_Address(x + 5, y);
            Write_text(0x00);
            i++;
            x += 6;
            if (x >= 128)
                x = 1;
        }
        else
            i++;
    }
}

void OLED_Grafix::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep)
    {
        swap(x0, y0);
        swap(x1, y1);
    }
    if (x0 > x1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1)
    {
        ystep = 1;
    }
    else
    {
        ystep = -1;
    }

    for (; x0 <= x1; x0++)
    {
        if (steep)
            Draw_Pixel(y0, x0);
        else
            Draw_Pixel(x0, y0);
        err -= dy;

        if (err < 0)
        {
            y0 += ystep;
            err += dx;
        }
    }
}

void OLED_Grafix::circleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corner)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (corner & 0x4)
        {
            Draw_Pixel(x0 + x, y0 + y);
            Draw_Pixel(x0 + y, y0 + x);
        }
        if (corner & 0x2)
        {
            Draw_Pixel(x0 + x, y0 - y);
            Draw_Pixel(x0 + y, y0 - x);
        }
        if (corner & 0x8)
        {
            Draw_Pixel(x0 - y, y0 + x);
            Draw_Pixel(x0 - x, y0 + y);
        }
        if (corner & 0x1)
        {
            Draw_Pixel(x0 - y, y0 - x);
            Draw_Pixel(x0 - x, y0 - y);
        }
    }
}

void OLED_Grafix::FCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (corner & 0x1)
        {
            Draw_FastVLine(x0 + x, y0 - y, 2 * y + 1 + delta);
            Draw_FastVLine(x0 + y, y0 - x, 2 * x + 1 + delta);
        }
        if (corner & 0x2)
        {
            Draw_FastVLine(x0 - x, y0 - y, 2 * y + 1 + delta);
            Draw_FastVLine(x0 - y, y0 - x, 2 * x + 1 + delta);
        }
    }
}

