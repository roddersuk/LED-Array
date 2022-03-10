#ifndef CANVAS_H_
#define CANVAS_H_

#include <stdint.h>
#include <Arduino.h>
#include <FastLED.h>
#include "debug.h"

// Connected to 74HC4067 mux/demux
#define DATA_PIN D1
#define ENABLE0_PIN D6
#define ENABLE1_PIN D7
#define S0_PIN D2
#define S1_PIN D3
#define S2_PIN D4
#define S3_PIN D5

#define MAX_COLOURS 32

enum orientation_t
{
    VERTICAL,
    HORIZONTAL
};

class Canvas
{
protected:
private:
    int nColours = 0;
    CRGB palette[MAX_COLOURS + 1];
    uint8_t **pixels;
    CRGB *leds;
    void selectLEDString(uint8_t col);
    orientation_t orientation = orientation_t::VERTICAL;

public:
    Canvas(const uint8_t w, const uint8_t h);
    Canvas(const uint8_t w, const uint8_t h, const orientation_t o);
    ~Canvas();

    uint8_t addColour(CRGB c);
    void setBackground(CRGB bgd) { palette[0] = bgd; };
    void clear(void);
    uint8_t getPixel(uint8_t x, uint8_t y);
    void reset(void);
    void setPixel(uint8_t x, uint8_t y, uint8_t p);
    void show(void);

    uint16_t width;
    uint16_t height;
};

#endif