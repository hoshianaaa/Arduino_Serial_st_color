#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define DEBUG 0

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
char GetColor();

//送信データ形式:[header, color, data1, data2, data3]
uint8_t txbuf[] = {255, 0, 0, 0, 0};



void setup() {
  Serial.begin(9600);
  //カラーセンサセットアップ:失敗で無限ループ
  if (tcs.begin()) {
    if (DEBUG)Serial.println("Found color sensor");
  } else {
    if (DEBUG)Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop() {
  txbuf[1] = GetColor();//黄色:'y' 赤:'r' 青:'b' 無し:'n'
  for (int i = 0; i < sizeof(txbuf_0); i++)Serial.write(txbuf_0[i]);
}



char GetColor() {

  uint16_t clear, red, green, blue;

  tcs.getRawData(&red, &green, &blue, &clear);

  char color;
  if (red < 45 && green < 45 && blue > 25)color = 'b';
  else if (red > 50 && green > 30)color = 'y';
  else if (red > 35 && green  > 25 && blue > 15)color = 'r';
  else color = 'n';
  if (DEBUG) {
    Serial.print(" "); Serial.print(red);
    Serial.print(" "); Serial.print(green);
    Serial.print(" "); Serial.print(blue);
    Serial.print(" "); Serial.println(color);
  }
  return color;
}
