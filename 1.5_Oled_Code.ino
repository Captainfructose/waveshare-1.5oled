#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include "OLED_Grafix.h"

#include <SPI.h>
#include <Wire.h>

OLED_Driver oledd = OLED_Driver();
OLED_Grafix grafix = OLED_Grafix();

void setup()  {

  //Init GPIO
  pinMode(oled_cs, OUTPUT);
  pinMode(oled_rst, OUTPUT);
  pinMode(oled_dc, OUTPUT);

  //Init UART
  Serial.begin(9600);

#if INTERFACE_4WIRE_SPI
  //Init SPI
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

#elif INTERFACE_3WIRE_SPI

  pinMode(oled_sck, OUTPUT);
  pinMode(oled_din, OUTPUT);

#endif
  grafix.initScreen();
  grafix.setTextColor(GREEN);
  grafix.writeText(1,1,"Brandon's K40");
  grafix.setColor(WHITE);
  grafix.drawLine(0,10,128,10);
  grafix.drawCircle(85, 60, 20);

  Serial.begin(9600);
}

int count;
int count2;
boolean switcher = false;
void loop() {
  grafix.setBarColor(BLUE);
  grafix.setGraphColor(WHITE);
  grafix.setTextColor(WHITE);
  grafix.setGaugeText(true);
  grafix.drawGauge(20, 60, count, 100, 20);
  grafix.writeText(9, 25, "Temp");
  // grafix.writeNumber(15, 52, count);
  grafix.setColor(WHITE);
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos(count2 * (PI / 180)), 60 - (20 - 2) * sin(count2 * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 90) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 90) * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 180) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 180) * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 270) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 270) * (PI / 180)));
  grafix.setColor(BLACK);
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 14) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 14) * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 104) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 104) * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 194) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 194) * (PI / 180)));
  grafix.drawLine(85, 60, 85 - (20 - 2) * cos((count2 - 284) * (PI / 180)), 60 - (20 - 2) * sin((count2 - 284) * (PI / 180)));

  if (count == 100) {
    switcher = true;
  }
  if (count == 0) {
    switcher = false;
  }
  if (switcher == true) {
    count--;
  }
  if (switcher == false) {
    count++;
  }
  if (count2 > 360)
  {
    count2 = 0;
  }
  count2 += 2;
  
}
