#include "text.h"
#include "font.h"

Text::Text(std::string t, TextProperties tp, GraphicProperties gp) : Graphic::Graphic(gp)
{
	DEBUG_CALL("Text: constructor - %s\n", t.c_str());
	text = t;
	textProperties = tp;
	xstart = properties.xpos;
	ystart = properties.ypos;
	DEBUG_CALL("Text: constructor exit\n");
}

Text::~Text() {
	DEBUG_CALL("Text: destructor\n");
}

void Text::reset(void)
{
	DEBUG_CALL("Text: reset\n");
	properties.xpos = xstart;
	properties.ypos = ystart;
	initialised = false;
	DEBUG_CALL("Text: reset exit\n");
}

void Text::setPosition(Canvas *canvas)
{
	DEBUG_CALL("Text: setPosition\n");
	uint8_t width =
		(properties.rotation == ROTATE0 || properties.rotation == ROTATE180) ? canvas->width : canvas->height;
	uint8_t height =
		(properties.rotation == ROTATE0 || properties.rotation == ROTATE180) ? canvas->height : canvas->width;
	if (properties.hscroll > 0)
		properties.xpos += width;
	else if (properties.hscroll < 0)
		properties.xpos -= text.length() * TEXT_W;
	if (properties.vscroll > 0)
		properties.ypos -= TEXT_H;
	else if (properties.vscroll < 0)
		properties.ypos += height;
	DEBUG_CALL("Text: setPosition exit\n");
}

void Text::allocateColours(Canvas *canvas)
{
	DEBUG_CALL("Text: allocateColours\n");
	fgdId = canvas->addColour(textProperties.fgd);
	dimId = canvas->addColour(textProperties.fgd.fadeLightBy(128));
	DEBUG_CALL("Text: allocateColours exit\n");
}

void Text::antiAlias(Canvas *canvas)
{
	DEBUG_CALL("Text: antiAlias\n");
	for (int i = 0; i < canvas->height - 1; i++)
	{
		for (int j = 0; j < canvas->width - 1; j++)
		{
			if (canvas->getPixel(j, i) == fgdId && canvas->getPixel(j + 1, i + 1) == fgdId && canvas->getPixel(j, i + 1) != fgdId && canvas->getPixel(j + 1, i) != fgdId)
			{
				canvas->setPixel(j, i + 1, dimId);
				canvas->setPixel(j + 1, i, dimId);
			}
			if (canvas->getPixel(j + 1, i) == fgdId && canvas->getPixel(j, i + 1) == fgdId && canvas->getPixel(j, i) != fgdId && canvas->getPixel(j + 1, i + 1) != fgdId)
			{
				canvas->setPixel(j, i, dimId);
				canvas->setPixel(j + 1, i + 1, dimId);
			}
		}
	}
	DEBUG_CALL("Text: antiAlias exit\n");
}

void Text::render(Canvas *canvas)
{
	DEBUG_CALL("Text: render\n");
	if (!initialised)
	{
		setPosition(canvas);
		allocateColours(canvas);
		initialised = true;
	}
	uint16_t cols =
		(properties.rotation == ROTATE90 || properties.rotation == ROTATE270) ? canvas->height : canvas->width;
	for (uint8_t col = 0; col < cols; col++)
	{
		// Get the character that appears in this column
		uint8_t n = col - properties.xpos;
		if (n < 0 || n >= int(text.length() * TEXT_W)) // no character here
			continue;
		char c = text.at(n / TEXT_W);
		uint64_t bitmap = font[int(c) - 32];
		uint8_t xoffset = TEXT_W - 1 - ((col - properties.xpos) % TEXT_W);
		// For each row of the character
		for (uint8_t row = 0; row < TEXT_H; row++)
		{
			uint8_t yoffset = (TEXT_H - row - 1) * TEXT_W;
			bool pixel = ((bitmap >> (xoffset + yoffset)) & 1);
			if (pixel)
			{
				Point p = transform(Point(col, row), canvas->width,
									canvas->height);
				canvas->setPixel(p.x, p.y, fgdId);
			}
		}
	}
	if (textProperties.smooth)
		antiAlias(canvas);
	move(canvas->width, canvas->height, text.length() * TEXT_W, TEXT_H);
	DEBUG_CALL("Text: render exit\n");
}
