#include "graphic.h"

Graphic::Graphic(GraphicProperties g) :
		properties(g) {
	DEBUG_CALL("Graphic: constructor\n");
	DEBUG_CALL("Graphic: constructor exit\n");
}

Graphic::~Graphic() {
	DEBUG_CALL("Graphic: destructor\n");
}

void Graphic::move(uint8_t width, uint8_t height, uint8_t imageWidth,
		uint8_t imageHeight) {
	DEBUG_CALL("Graphic: move w=%d h=%d iw=%d ih=%d\n", width, height, imageWidth, imageHeight);
	properties.xpos -= properties.hscroll;
	properties.ypos += properties.vscroll;
	if (properties.hbounce) {
		if (properties.hscroll > 0) {
			if (properties.xpos < 0) {
				properties.xpos = 0;
				properties.hscroll = -properties.hscroll;
			}
		} else if (properties.hscroll < 0) {
			if (properties.xpos >= width - 1 - imageWidth) {
				properties.xpos = width - 1 - imageWidth;
				properties.hscroll = -properties.hscroll;
			}
		}
	}
	if (properties.vbounce) {
		if (properties.vscroll < 0) {
			if (properties.ypos <= 0) {
				properties.ypos = 0;
				properties.vscroll = -properties.vscroll;
			}
		} else if (properties.vscroll > 0) {
			if (properties.ypos > height - 1 - imageHeight) {
				properties.ypos = height - 1 - imageHeight;
				properties.vscroll = -properties.vscroll;
			}
		}
	}
	DEBUG_CALL("Graphic: move exit\n");
}

void Graphic::render(Canvas *c) {
	DEBUG_CALL("Graphic: render entry/exit\n");
}

void Graphic::setPosition(Canvas *canvas, uint8_t image_width, uint8_t image_height) {
	DEBUG_CALL("Graphic: setPosition iw=%d ih=%d\n", image_width, image_height);
	uint8_t width =
			(properties.rotation == ROTATE0 || properties.rotation == ROTATE180) ?
					canvas->width : canvas->height;
	uint8_t height =
			(properties.rotation == ROTATE0 || properties.rotation == ROTATE180) ?
					canvas->height : canvas->width;
	if (properties.hscroll > 0)
		properties.xpos += width;
	else if (properties.hscroll < 0)
		properties.xpos -= image_width;
	if (properties.vscroll > 0)
		properties.ypos -= image_height;
	else if (properties.vscroll < 0)
		properties.ypos += height;
	DEBUG_CALL("Graphic: setPosition exit\n");
}

Point Graphic::transform(Point p1, uint8_t width, uint8_t height) {
	DEBUG_CALL("Graphic: transform x=%d, y=%d w=%d h=%d\n", p1.x, p1.y, width, height);
	Point p2;
	switch (properties.rotation) {
	default:
	case ROTATE0:
		p2.x = p1.x;
		p2.y = p1.y + properties.ypos;
		break;
	case ROTATE90:
		p2.x = p1.y + properties.ypos;
		p2.y = height - 1 - p1.x;
		break;
	case ROTATE180:
		p2.x = width - 1 - p1.x;
		p2.y = height - 1 - p1.y - properties.ypos;
		break;
	case ROTATE270:
		p2.x = width - 1 - p1.y - properties.ypos;
		p2.y = p1.x;
		break;
	}
	if (properties.hflip) {
		p2.x = width - 1 - p2.x;
	}
	if (properties.vflip) {
		p2.y = height - 1 - p2.y;
	}
	DEBUG_CALL("Graphic: transform exit x=%d y=%d\n", p2.x, p2.y);
	return p2;
}
