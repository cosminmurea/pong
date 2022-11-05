#include "Racket.h"

const int Racket::width = 10;
const int Racket::height = 100;
const int Racket::speed = 8;

Racket::Racket(float x, float y) {
    this->x = x;
    this->y = y;
}

float Racket::getX() {
    return this->x;
}

float Racket::getY() {
    return this->y;
}

const int Racket::getWidth() {
    return width;
}

const int Racket::getHeight() {
    return height;
}

const int Racket::getSpeed() {
    return speed;
}

void Racket::setX(float x) {
    this->x = x;
}

void Racket::setY(float y) {
    this->y = y;
}
