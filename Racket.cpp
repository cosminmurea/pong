#include "Racket.h"

// The 'this' keyword is only used when needed (eg. parameters named the same as the data members).

const int Racket::width = 10;
const int Racket::height = 100;
const int Racket::speed = 4;

Racket::Racket(float x, float y) {
    this->x = x;
    this->y = y;
}

float Racket::getX() {
    return x;
}

float Racket::getY() {
    return y;
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