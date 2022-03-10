#include <Arduino.h>
#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>
#include <string>

#include "debug.h"
#include "text.h"
#include "image.h"
#include "scene.h"
#include "sprites.h"

#pragma message "LED Array Demonstrator"

#define LEDS_PER_STRING 30
#define NUM_LED_STRINGS 16

#define FRAMES_PER_SECOND 25
#define FRAME_DELAY 100 / FRAMES_PER_SECOND
#define SCENE_DURATION_SECONDS 15
#define NUM_SCENES 3

int scene_no = 0;
int countdown = 0;
Canvas *canvas;
Scene *scene;
GraphicProperties gp = {.hscroll = 1};
GraphicProperties gp2 = {.ypos = 15, .hscroll = -1};
GraphicProperties gp3 = {
    .ypos = 10,
    .rotation = rotation_t::ROTATE90,
    .hscroll = 1,
    .vscroll = 1,
    .vbounce = true};
GraphicProperties gp4 = {.hscroll = 1, .vscroll = 1, .hbounce = true, .vbounce = true};
GraphicProperties gp5 = {.vscroll = 1};
TextProperties tp = {.fgd = CRGB::Yellow, .smooth = true};

void setup()
{
  Serial.begin(115200);
  delay(3000);
  DEBUG_MSG("setup: booting up...\n");
  canvas = new Canvas(NUM_LED_STRINGS, LEDS_PER_STRING, orientation_t::VERTICAL);
  scene = new Scene(canvas);
}

void loop2() {
  if (countdown <= 0) {
    canvas->addColour(CRGB::Black);
    canvas->addColour(CRGB::White);
    canvas->addColour(CRGB::Red);
    canvas->addColour(CRGB::Green);
    canvas->addColour(CRGB::Blue);
    canvas->setBackground(1);
    canvas->setPixel(0, 0, 1);
    canvas->setPixel(0, 1, 2);
    canvas->setPixel(0, 2, 3);
    canvas->setPixel(0, 3, 4);
    canvas->setPixel(0, 4, 5);
    countdown = 1;
  }
  canvas->show();
} 
// TODO: countdown not right
// TODO: flickering 
// TDOD: freezing - power?

void loop()
{
  DEBUG_CALL("loop: countdown=%d\n", countdown);
  if (countdown <= 0)
  {
    // new scene
    DEBUG_MSG("New scene %d\n", scene_no);
    scene->clear();
    switch (scene_no)
    {
    case 0:
      scene->add(new Image(TREE_WIDTH, TREE_HEIGHT, tree[0], TREE_COLOURS, tree_colours, gp4));
      break;
    case 1:
      scene->add(new Text("Merry Christmas", tp, gp));
      scene->add(new Text("Everyone", tp, gp2));
      scene->add(new Image(SNOW_WIDTH, SNOW_HEIGHT, snow[0], SNOW_COLOURS, snow_colours, gp5));
      scene->add(new Image(SNOW_WIDTH, SNOW_HEIGHT, snow[0], SNOW_COLOURS, snow_colours, gp5));
      scene->add(new Image(SNOW_WIDTH, SNOW_HEIGHT, snow[0], SNOW_COLOURS, snow_colours, gp5));
      scene->add(new Image(SNOW_WIDTH, SNOW_HEIGHT, snow[0], SNOW_COLOURS, snow_colours, gp5));
      scene->setPosition(2, 5, -15);
      scene->setPosition(3, 15, 0);
      scene->setPosition(4, 25, -75);
      scene->setPosition(5, 10, -50);
      break;
    case 2:
      scene->add(new Text("and a Happy New Year", tp, gp3));
      break;
    }
    scene_no = (scene_no + 1) % NUM_SCENES;
    countdown = SCENE_DURATION_SECONDS * FRAMES_PER_SECOND;
    // countdown = 1;
  }
  scene->render();
  canvas->show();
  delay(FRAME_DELAY);
  canvas->clear();
  countdown--;
  DEBUG_CALL("loop: end of loop\n");
}