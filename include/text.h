#ifndef TEXT_H_
#define TEXT_H_

#include <stdint.h>
#include <string>
#include "debug.h"
#include "graphic.h"

struct TextProperties
{
	CRGB fgd = CRGB::White;
	bool smooth = false;
};

class Text : public Graphic
{
protected:
private:
	void antiAlias(Canvas *canvas);
	void allocateColours(Canvas *canvas);
	void setPosition(Canvas *canvas);

	std::string text;
	TextProperties textProperties;
	uint8_t xstart;
	uint8_t ystart;
	char fgdId = 0;
	char dimId = 0;
	bool initialised = false;

public:
	Text(std::string t, TextProperties tp, GraphicProperties gp);
	~Text();

	void reset(void);
	void setText(std::string t) {text = t;};
	void render(Canvas *c);
};

#endif /* TEXT_H_ */
