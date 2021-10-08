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
  grafix.writeText(1,1,"1.5 inch display test");
  grafix.setColor(YELLOW);
  grafix.drawLine(0,10,128,10);
  grafix.setTextColor(CYAN);
  grafix.writeText(1,20,"Ammo:");
  grafix.setColor(YELLOW);
  grafix.drawLine(0,30,128,30);
  grafix.setColor(CYAN);

  Serial.begin(9600);
}

int count;
boolean switcher = false;
void loop() {
  grafix.setBarColor(GREEN);
  grafix.setGraphColor(WHITE);
  grafix.setTextColor(BLUE);
  grafix.HBarGraph(50, 19, 60, 10, count, 100);
  grafix.VBarGraph(2, 60, 10, 60, count, 100);
  grafix.drawGauge(60, 70, count, 100, 30);
  grafix.drawGauge(40, 120, count, 100, 20);
  grafix.drawGauge(85, 120, count, 100, 20);

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

  grafix.printNum(30, 20, count);
  
  
}
