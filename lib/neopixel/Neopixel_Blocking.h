#ifndef NEOPIXEL_BLOCKING_H
#define NEOPIXEL_BLOCKING_H
#include "mbed.h"

/*
    Data is written in G -> R -> B
    Each byte is a number value from 0-255 of the intensity of that individual LED light
*/

class Neopixel_Blocking
{
private:
    int pixelNum;
    int on_buffer[8] = {1,1,1,1,1,1,1,1};
    int off_buffer[8] = {0};
    DigitalOut out;
public:
    Neopixel_Blocking(int numPixels, PinName mtrxPinName);
    ~Neopixel_Blocking();
    void pulse_1();
    void pulse_0();
    void writeByte(const int buffer[8]);
    void showColour(char colour);
    void blinkPixels(int flashes, char colour);
    void writeAnyRGB(const int colour[3]);
    void writeAnyRGBall(const int colour[3]);

    //basic functions for autonomy
    void displayRed();
    void displayBlue();
    void flashGreen(int numFlashes, float delay_s);
    void shutdown();
    void overwriteFirstBit(char colour);
};

#endif /* Neopixel_Blocking_H */