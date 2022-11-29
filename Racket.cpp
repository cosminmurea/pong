#include "Racket.h"

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

void Racket::draw() {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    glEnd();
}

void Racket::move(bool moveUp, bool moveDown, int windowHeight) {
    if ((moveUp) && (y < windowHeight - height - 10)) {
        y = y + speed;
    }
    if ((moveDown) && (y > 10)) {
        y = y - speed;
    }
}
