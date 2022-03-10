#ifndef SCENE_H_
#define SCENE_H_
/* This is the class for the objects in a scene */

#include <stdint.h>
// #include <vector>
#include <memory>
#include "debug.h"
#include "canvas.h"
#include "graphic.h"

#define MAX_GRAPHICS 10

//#define add(X) graphics.emplace_back(X)

class Scene
{
protected:
    Canvas *canvas;
    Graphic *graphics[MAX_GRAPHICS];
    // std::vector<std::unique_ptr<Graphic>> graphics;
public:
    Scene(Canvas *c);
    void clear(void);
    void render(void);
    void setPosition(uint8_t n, int x, int y);
    void add(Graphic *g);
    uint8_t nGraphics = 0;
};

#endif /* SCENE_H_ */