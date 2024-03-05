//
// Created by Ryan on 2/25/2024.
//

#include "main.h"
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

// Use hardware SPI (fast, but fixed SPI pins)
#define TFT_CS D2 // Chip select
#define TFT_RST D4 // Reset
#define TFT_DC D3 // Data and Command

// Touch Screen
#define CS_PIN D8 //TouchScreen Chip Select Pin
#define TIRQ_PIN D1 //TouchScreen IRQ Pin

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);

void setup(){
    Serial.begin(9600);

// Begin the touchscreen
    ts.begin();
    ts.setRotation(1); // Depending on your screen's orientation

    tft.begin();
    tft.setRotation(3); //Adjust as needed

}

void loop(){
    static unsigned long lastTouchTime = 0;
    const unsigned long touchDebounceTime = 200; // 200 milliseconds

    if (ts.touched() && (millis() - lastTouchTime > touchDebounceTime)) {
        lastTouchTime = millis(); // Update the last touch time
        TS_Point p = ts.getPoint();
        tft.fillScreen(ILI9341_WHITE);
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(0,0);
        tft.setTextSize(2);
        tft.print("X = ");
        tft.print(p.x);
        tft.print(" Y = ");
        tft.println(p.y);

        
    } else {

        tft.fillScreen(ILI9341_BLACK);
        tft.setTextColor(ILI9341_WHITE);
        tft.setCursor(0, 0);
        tft.setTextSize(1);
        tft.println("Hello, World!");
    }
    delay(200);
}