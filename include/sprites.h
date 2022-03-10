/*
 * sprites.h
 *
 *  Created on: 14 Feb 2022
 *      Author: rod
 */

#ifndef SPRITES_H_
#define SPRITES_H_

#include <stdint.h>
#include <FastLED.h>
#include "debug.h"

#define TREE_WIDTH 9
#define TREE_HEIGHT 11
#define TREE_COLOURS 4

#define SNOW_WIDTH 5
#define SNOW_HEIGHT 5
#define SNOW_COLOURS 1

uint8_t tree[][TREE_WIDTH] = {
	{0, 0, 0, 0, 3, 0, 0, 0, 0},
	{0, 0, 0, 0, 2, 0, 0, 0, 0},
	{0, 0, 0, 2, 2, 2, 0, 0, 0},
	{0, 0, 1, 2, 2, 2, 1, 0, 0},
	{0, 0, 2, 2, 2, 2, 2, 0, 0},
	{0, 0, 1, 2, 2, 2, 1, 0, 0},
	{0, 2, 2, 2, 2, 2, 2, 2, 0},
	{0, 1, 2, 2, 2, 2, 2, 3, 0},
	{2, 2, 2, 2, 2, 2, 2, 2, 2},
	{0, 0, 0, 4, 4, 4, 0, 0, 0},
	{0, 0, 0, 4, 4, 4, 0, 0, 0}
};

CRGB tree_colours[TREE_COLOURS] = {CRGB::Red, CRGB::Green, CRGB::Gold, CRGB::Brown};

uint8_t snow[][SNOW_WIDTH] = {
		{0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1},
		{0, 1, 1, 1, 0},
		{1, 0, 1, 0, 1},
		{0, 1, 0, 1, 0}
};

CRGB snow_colours[SNOW_COLOURS] = {CRGB::White};

#endif /* SPRITES_H_ */
