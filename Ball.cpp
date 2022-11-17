#include "Ball.h"
#include <cmath>

// The 'this' keyword is only used when needed (eg. parameters named the same as the data members).

const int Ball::speed = 7;
const int Ball::size = 8;

Ball::Ball(float posX, float posY, float dirX, float dirY) {
    this->posX = posX;
    this->posY = posY;
    this->dirX = dirX;
    this->dirY = dirY;
}

float Ball::getPosX() {
    return posX;
}

float Ball::getPosY() {
    return posY;
}

float Ball::getDirX() {
    return dirX;
}

float Ball::getDirY() {
    return dirY;
}

const int Ball::getSpeed() {
    return speed;
}

const int Ball::getSize() {
    return size;
}

void Ball::setPosX(float posX) {
    this->posX = posX;
}

void Ball::setPosY(float posY) {
    this->posY = posY;
}

void Ball::setDirX(float dirX) {
    this->dirX = dirX;
}

void Ball::setDirY(float dirY) {
    this->dirY = dirY;
}

void Ball::normalizeVector() {
    float magnitude = sqrt((dirX * dirX) + (dirY * dirY));
    if (magnitude != 0.0f) {
        magnitude = 1.0f / magnitude;
        dirX *= magnitude;
        dirY *= magnitude;
    }
}
