//
// Created by Ryan on 2/25/2024.
//

#include "main.h"
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Use hardware SPI (fast, but fixed SPI pins)
#define TFT_CS D2
#define TFT_RST D4
#define TFT_DC D3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup(){
    tft.begin();
    tft.setRotation(3); //Adjust as needed
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Hello, World!");
}

void loop(){
    //Nothing here
}