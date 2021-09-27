#include "OLED_Driver.h"
#include "OLED_GFX.h"
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
  Serial.begin(115200);

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

void loop() {
  grafix.setBarColor(GREEN);
  grafix.setGraphColor(WHITE);
  grafix.setTextColor(BLUE);
  grafix.HBarGraph(50, 19, 60, 10, count, 60);
  grafix.VBarGraph(2, 60, 10, 60, count, 60);
  grafix.drawGauge(40,50,10,10,10);
  
  if (count >= 60) {
    count = 0;

  }

  grafix.printNum(30, 20, count);
  

  count++;
  delay(100);
}
