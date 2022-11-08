#include "Ball.h"
#include <cmath>

const int Ball::speed = 3;
const int Ball::size = 10;

Ball::Ball(float posX, float posY, float dirX, float dirY) {
    this->posX = posX;
    this->posY = posY;
    this->dirX = dirX;
    this->dirY = dirY;
}

float Ball::getPosX() {
    return this->posX;
}

float Ball::getPosY() {
    return this->posY;
}

float Ball::getDirX() {
    return this->dirX;
}

float Ball::getDirY() {
    return this->dirY;
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
    float magnitude = sqrt((this->dirX * this->dirX) + (this->dirY * this->dirY));
    if (magnitude != 0.0f) {
        magnitude = 1.0f / magnitude;
        this->dirX *= magnitude;
        this->dirY *= magnitude;
    }
}
