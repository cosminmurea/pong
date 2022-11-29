#include "Ball.h"

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

void Ball::draw() {
    int triangleAmount = 18;
    float twicePI = 2 * M_PI;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(posX, posY);
        for (int i = 0; i <= triangleAmount; i++) {
            float tempX = posX + (size * cos(i * twicePI / triangleAmount));
            float tempY = posY + (size * sin(i * twicePI / triangleAmount));
            glVertex2f(tempX, tempY);
        }
    glEnd();
}

void Ball::move(int& scoreLeft, int& scoreRight, float racketLeftX, float racketLeftY, float racketRightX, float racketRightY, const int racketWidth, const int racketHeight, int windowWidth, int windowHeight) {
    // Start by flying straight to the left.
    posX = posX + dirX * speed;
    posY = posY + dirY * speed;

    // Collisions
    //  1. Top border
    if (posY > windowHeight - size - 10) {
        dirY = -fabs(dirY);
    }
    //  2. Bottom border
    if (posY < size + 10) {
        dirY = fabs(dirY);
    }
    //  3. Left border
    if (posX < size) {
        scoreRight++;
        posX = windowWidth / 2.0f;
        posY = windowHeight / 2.0f;
        dirX = fabs(dirX);
        dirY = 0;
    }
    //  4. Right border
    if (posX > windowWidth - size) {
        scoreLeft++;
        posX = windowWidth / 2.0f;
        posY = windowHeight / 2.0f;
        dirX = -fabs(dirX);
        dirY = 0;
    }
    //  5. Left racket
    if ((posX <= racketLeftX + racketWidth + size) &&
        (posY <= racketLeftY + racketHeight + size) &&
        (posY >= racketLeftY - size)) {
            dirX = fabs(dirX);
            // Changes the trajectory of the ball based on where it collided with the racket.
            // It returns a value between [-0.5, 0.5] : 0.5 if it hits the top of the paddle and -0.5 for the bottom.
            float trajChange = (posY - racketLeftY) / racketHeight - 0.5f;
            dirY = trajChange;
    }
    //  6. Right racket
    if ((posX >= racketRightX - size) &&
        (posY <= racketRightY + racketHeight + size) &&
        (posY >= racketRightY - size)) {
            dirX = -fabs(dirX);
            float trajChange = (posY - racketRightY) / racketHeight - 0.5f;
            dirY = trajChange;
    }

    normalizeVector();
}

void Ball::normalizeVector() {
    float magnitude = sqrt((dirX * dirX) + (dirY * dirY));
    if (magnitude != 0.0f) {
        magnitude = 1.0f / magnitude;
        dirX *= magnitude;
        dirY *= magnitude;
    }
}
