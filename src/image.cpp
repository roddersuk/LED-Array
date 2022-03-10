/*
 * image.cpp
 *
 *  Created on: 13 Feb 2022
 *      Author: rod
 */

#include "image.h"

Image::Image(uint8_t w, uint8_t h, uint8_t *p, uint8_t nc, CRGB *c, GraphicProperties &gp) : Graphic::Graphic(gp)
{
	DEBUG_CALL("Image: constructor %dx%d nc=%d\n", w, h, nc);
	width = w;
	height = h;
	pixels = p;
	no_colours = nc;
	colours = c;
	DEBUG_CALL("Image: constructor exit\n");
}

Image::~Image()
{
	DEBUG_CALL("Image: destructor\n");
	// TODO Auto-generated destructor stub
}

void Image::allocateColours(Canvas *canvas)
{
	DEBUG_CALL("Image: allocateColours\n");
	for (int i = 0; i < no_colours; i++)
	{
		DEBUG_MSG("Image: allocateColours adding colour R%2x G%2x B%2x\n", colours[i].r, colours[i].g, colours[i].b);
		colour_map[i+1] = canvas->addColour(colours[i]);
	}
	DEBUG_CALL("Image: allocateColours exit\n");
}

void Image::render(Canvas *canvas)
{
	DEBUG_CALL("Image: render\n");
	if (!initialised)
	{
		setPosition(canvas, width, height);
		allocateColours(canvas);
		initialised = true;
		DEBUG_MSG("Image initialised\n");
	}
	uint16_t cols =
		(properties.rotation == ROTATE90 || properties.rotation == ROTATE270) ? canvas->height : canvas->width;
	DEBUG_MSG("Image: render column loop\n");
	for (uint8_t col = 0; col < cols; col++)
	{
		// Get the pixel that appears in this column
		uint8_t n = col - properties.xpos;
		if (n < 0 || n >= width) // no pixel here
			continue;
		// For each row of the image
		for (uint8_t row = 0; row < height; row++)
		{
			uint8_t pixel = pixels[row * width + n];
			if (pixel > 0)
			{
				Point p = transform(Point(col, row), canvas->width, canvas->height);
				canvas->setPixel(p.x, p.y, colour_map[pixel]);
			}
		}
	}
	move(canvas->width, canvas->height, width, height);
	DEBUG_CALL("Image: render exit\n");
}
