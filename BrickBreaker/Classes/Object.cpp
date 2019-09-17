#include "Object.h"

Object::Object(SDL_Renderer* renderer) {
    this->renderer = renderer;
    x = 0;
    y = 0;
    width = 1;
    height = 1;
}

Object::~Object() {
}
Object::Object() {
}

