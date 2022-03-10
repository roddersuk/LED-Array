#ifndef GRAPHIC_H_
#define GRAPHIC_H_
/* This is the base class for the objects in a scene */

#include <stdint.h>
#include "debug.h"
#include "canvas.h"

enum rotation_t {ROTATE0, ROTATE90, ROTATE180, ROTATE270};

struct GraphicProperties
{
    int xpos = 0; // current position of top left of graphic in pixels
    int ypos = 0;
    rotation_t rotation = ROTATE0;
    int8_t hscroll = 0;   // horizontal scroll increment, positive left
    int8_t vscroll = 0;   // vertical scroll increment, positive down
    bool hbounce = false; // reverse motion when reaching the edge horizontally
    bool vbounce = false; // reverse motion when reaching the edge vertically
    bool hflip = false;    // flip the graphic horizontally
    bool vflip = false;  // flip the graphic vertically
};

struct Point {
	uint8_t x = 0;
	uint8_t y = 0;
	Point() {};
	Point(uint8_t x, uint8_t y) : x(x), y(y) {};
};

class Graphic
{
protected:
	void move(uint8_t width, uint8_t height, uint8_t imageWidth, uint8_t imageHeight);
	void setPosition(Canvas *canvas, uint8_t image_width, uint8_t image_height);
	Point transform(Point, uint8_t width, uint8_t height);
private:
public:
    Graphic(GraphicProperties g);
    virtual ~Graphic(void);
    virtual void render(Canvas *c);

    GraphicProperties properties;
};

#endif /* GRAPHIC_H_ */
