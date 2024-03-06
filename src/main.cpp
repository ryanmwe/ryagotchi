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

    // Begin the screen
    tft.begin();
    tft.setRotation(3); //Adjust as needed 

    // Dynamically retrieve screen width and height
    int screenWidth = tft.width();
    int screenHeight = tft.height();

    // Debug: Print screen dimensions to Serial
    // tft.print("Screen Width: ");
    // tft.println(screenWidth);
    // tft.print("Screen Height: ");
    // tft.println(screenHeight);

}

void drawButtons(int screenWidth, int screenHeight) {
    // Define button dimensions
    const int btnHeight = 65;
    const int btnWidths[] = {65, 65, 65, 65, screenWidth - 4 * 65};
    int yPos = screenHeight - btnHeight; //y positon of buttons

    uint16_t btnColor = ILI9341_BLUE;
    uint16_t textColor = ILI9341_WHITE;

    // Iterate throught he button widths array to draw each butotn
    int xPos = 0; // Starting x positiong for the first button
    // Draw the first four buttons
    for (int i = 0; i < 5; i++) {
        tft.fillRect(xPos, yPos, btnWidths[i], btnHeight, btnColor);

        tft.setTextColor(textColor);
        tft.setTextSize(2);

        // Calculate text position for centered alignment (adjust as necessary)
        int textX = xPos + (btnWidths[i] / 2) - 10; // Adjust text position based on button width
        int textY = yPos + (btnHeight / 2) - 8; // Adjust text Y position for vertical centering

        // Print button label
        tft.setCursor(textX, textY);
        tft.println("B" + String(i+1));

        // Update xPos for the next button
        xPos += btnWidths[i];
    }

}
void loop(){
    int screenWidth = tft.width();
    int screenHeight = tft.height();
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
    } 
    drawButtons(screenWidth, screenHeight);
    delay(200);
}