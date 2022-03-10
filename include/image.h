/*
 * image.h
 *
 *  Created on: 13 Feb 2022
 *      Author: rod
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include <stdint.h>
#include "debug.h"
#include "graphic.h"

class Image : public Graphic{
private:
	uint8_t width = 0;
	uint8_t height = 0;
	uint8_t *pixels;
	uint8_t no_colours = 0;
	uint8_t colour_map[MAX_COLOURS];
	CRGB *colours;
	bool initialised = false;

	void allocateColours(Canvas *c);
public:
	Image(uint8_t w, uint8_t h, uint8_t *p, uint8_t nc, CRGB *c, GraphicProperties &gp);
	~Image();

	void render(Canvas *c);
};

#endif /* IMAGE_H_ */
