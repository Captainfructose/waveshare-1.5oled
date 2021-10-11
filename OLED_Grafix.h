#ifndef __OLED_GRAFIX_H
#define __OLED_GRAFIX_H


#include "OLED_Driver.h"

#define PI 3.14159


class OLED_Grafix : public virtual OLED_Driver{
    
    public:
        OLED_Grafix(void);
        float old_value;
        float first_value;

        void setBarColor(uint16_t color);
        void setGraphColor(uint16_t color);
        void setTextColor(uint16_t color);
        void setGaugeText(bool text);
        void initScreen(void);
        void HBarGraph(int x, int y, float w, int h, float value, float maxi);
        void VBarGraph(int x, int y, int w, float h, float value, float maxi);
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h);
        void drawFRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
        void drawCircle(int16_t x0, int16_t y0, int16_t r);
        void drawFCircle(int16_t x0, int16_t y0, int16_t r);
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r);
        void drawGauge(uint16_t x, uint16_t y, uint16_t value, uint16_t max, uint16_t radius);
        void setColor(const uint8_t *text);
        void setFillColor(const uint8_t *text);
        void writeNumber(uint8_t x, uint8_t y, uint8_t num);
        void writeText(uint8_t x, uint8_t y, const uint8_t *text);

    private :
        uint16_t bar_color;
        uint16_t graph_color;
        uint16_t text_color;
        bool text_status;
        
        void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
        void circleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corner);
        void FCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta);
};

#endif