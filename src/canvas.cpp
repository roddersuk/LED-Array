#include "canvas.h"

Canvas::Canvas(const uint8_t w, const uint8_t h) : width(w), height(h)
{
    DEBUG_CALL("Canvas: constructor %dx%d\n", width, height);
    // Create main arrays
    leds = new CRGB[height];
    pixels = new uint8_t *[width];
    for (int i = 0; i < width; i++)
    {
        pixels[i] = new uint8_t[height];
    }

    // Initialise pins
    pinMode(DATA_PIN, OUTPUT);
    pinMode(ENABLE0_PIN, OUTPUT);
    pinMode(ENABLE1_PIN, OUTPUT);
    pinMode(S0_PIN, OUTPUT);
    pinMode(S1_PIN, OUTPUT);
    pinMode(S2_PIN, OUTPUT);
    pinMode(S3_PIN, OUTPUT);

    // Setup leds N.B. GRB arrangement
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, height);

    reset();
    DEBUG_CALL("Canvas: constructor exit\n");
}

Canvas::Canvas(const uint8_t x, const uint8_t y, orientation_t o) : Canvas::Canvas(x, y)
{
    orientation = o; // VERTICAL means the LED strings are vertical
}

Canvas::~Canvas()
{
}

uint8_t Canvas::addColour(CRGB c)
{
    DEBUG_CALL("Canvas: addColour R%x G%x B%x\n", c.r, c.g, c.b);
    // N.B. 0 is background
    uint8_t colour = nColours;
    bool found = false;
    // If the colour is already in the palette return its index
    for (int i = 0; i < nColours + 1; i++)
    {
        if (palette[i].r == c.r && palette[i].g == c.g && palette[i].b == c.b)
        {
            found = true;
            DEBUG_MSG("Canvas: addColour found existing colour %d\n", i);
            colour = i;
            break;
        }
    }
    // Otherwise allocate a new colour if there is room
    if (!found && nColours < MAX_COLOURS)
    {
        palette[++nColours] = c;
        colour = nColours;
    }
#ifdef DEBUG_ESP_PORT
    DEBUG_MSG("Canvas: addColour: palette (%d): ", nColours);
    for (int i = 0; i < nColours + 1; i++)
    {
        DEBUG_MSG("%d R%x G%x B%x, ", i, palette[i].r, palette[i].g, palette[i].b);
    }
    DEBUG_MSG("\n");
#endif /* DEBUG_ESP_PORT */
    DEBUG_CALL("Canvas: addColour returning %d\n", colour);
    return colour;
}

void Canvas::clear(void)
{
    DEBUG_CALL("Canvas: clear\n");
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pixels[i][j] = 0;
        }
    }
    DEBUG_CALL("Canvas: clear exit\n");
}

void Canvas::reset(void)
{
    DEBUG_MSG("Canvas: reset\n");
    clear();
    nColours = 0;
    setBackground(CRGB::Black);
    DEBUG_CALL("Canvas: reset exit\n");
}

void Canvas::setPixel(uint8_t x, uint8_t y, uint8_t p)
{
    // DEBUG_CALL("Canvas: setPixel: x=%d y=%d p=%d\n", x, y, p);
    if (x >= 0 && x < width && y >= 0 && y < height)
        pixels[x][y] = p;
}

uint8_t Canvas::getPixel(uint8_t x, uint8_t y)
{
    // DEBUG_CALL("Canvas: getPixel: x=%d y=%d\n", x, y);
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        // DEBUG_CALL("Canvas: getPixel returns %d\n", pixels[x][y]);
        return pixels[x][y];
    }
    else
    {
        // DEBUG_CALL("Canvas: getPixel returns 0\n");
        return 0;
    }
}

// TODO: Support fancy backgrounds
void Canvas::show(void)
{
    DEBUG_CALL("Canvas: show %dx%d\n", width, height);

    for (int col = 0; col < width; col++)
    {
        // fill_solid(leds, height, background);
        DEBUG_MSG("Canvas: show: Pixels in string %d: ", col);
        for (int row = 0; row < height; row++)
        {
            DEBUG_MSG("%d ", pixels[col][row]);
            leds[row] = palette[(pixels[col][row])];
        }
        DEBUG_MSG("\n");
#ifdef DEBUG_ESP_PORT
        DEBUG_MSG("Canvas: show: Colours in leds: ");
        for (int row = 0; row < height; row++)
        {
            DEBUG_MSG("%d,%d,%d ", leds[row].r, leds[row].g, leds[row].b);
        }
        DEBUG_MSG("\n");
#endif /* DEBUG_ESP_PORT */
        DEBUG_MSG("Canvas: show string %d\n", col);
        selectLEDString(col);
        FastLED.show();
    }
    DEBUG_CALL("Canvas: show exit\n");
}

void Canvas::selectLEDString(uint8_t n)
{
    DEBUG_CALL("Canvas: selectLEDString %d\n", n);
    // Set enable pins and address for up to 32 strings (0 - 31)
    // If more that 32 will be treated as 16-31

    // Enable the appropriate demux
    if (n < 16)
    {
        digitalWrite(ENABLE0_PIN, LOW);
        digitalWrite(ENABLE1_PIN, HIGH);
    }
    else
    {
        digitalWrite(ENABLE1_PIN, LOW);
        digitalWrite(ENABLE0_PIN, HIGH);
    }

    // Set the demux address
    digitalWrite(S0_PIN, (n & 1) ? HIGH : LOW);
    digitalWrite(S1_PIN, (n & 2) ? HIGH : LOW);
    digitalWrite(S2_PIN, (n & 4) ? HIGH : LOW);
    digitalWrite(S3_PIN, (n & 8) ? HIGH : LOW);

    // Wait for switch?
    delayMicroseconds(10);

    DEBUG_CALL("Canvas: selectLEDString exit\n");
}
