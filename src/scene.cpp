#include "scene.h"

Scene::Scene(Canvas *c) : canvas(c) {
    DEBUG_CALL("Scene: constructor\n");
    DEBUG_CALL("Scene: constructor exit\n");
}

void Scene::add(Graphic *g) {
    DEBUG_CALL("Scene: add\n");
    if (nGraphics < MAX_GRAPHICS) {
        DEBUG_MSG("Scene: add adding graphics %d\n", nGraphics);
        graphics[nGraphics] = g;
        nGraphics++;
    }
    DEBUG_CALL("Scene: add exit - total graphics %d\n", nGraphics);
}

void Scene::clear(void) {
    DEBUG_CALL("Scene: clear\n");
    for (int i = 0; i < nGraphics; i++) {
        delete graphics[i];
    }
    nGraphics = 0;
    canvas->reset();
    DEBUG_CALL("Scene: clear exit\n");
}

void Scene::render(void) {
    DEBUG_CALL("Scene: render %d graphics\n", nGraphics);
    for (int i = 0; i < nGraphics; i++) {
        graphics[i]->render(canvas);
    }
    DEBUG_CALL("Scene: render exit\n");
}

void Scene::setPosition(uint8_t n, int x, int y) {
    DEBUG_CALL("Scene: setPosition n=%d, x=%d, y=%d\n", n, x, y);
	graphics[n]->properties.xpos = x;
	graphics[n]->properties.ypos = y;
    DEBUG_CALL("Scene: setPosition exit\n");
}