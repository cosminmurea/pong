#include "Window.h"
#include <GL/freeglut.h>
#include <cmath>

const int Window::updateRate = 1000 / 60;

Window::Window(int width, int height) {
    this->width = width;
    this->height = height;
    this->scoreLeft = 0;
    this->scoreRight = 0;
}

int Window::getWidth() {
    return this->width;
}

int Window::getHeight() {
    return this->height;
}

int Window::getScoreLeft() {
    return this->scoreLeft;
}

int Window::getScoreRight() {
    return this->scoreRight;
}

const int Window::getUpdateRate() {
    return updateRate;
}

void Window::setWidth(int width) {
    this->width = width;
}

void Window::setHeight(int height) {
    this->height = height;
}

void Window::setScoreLeft(int scoreLeft) {
    this->scoreLeft = scoreLeft;
}

void Window::setScoreRight(int scoreRight) {
    this->scoreRight = scoreRight;
}

void Window::drawHCenteredText(void* textFont, int yOffset, std::string text, bool fullScreenFlag) {
    float textPosX, textPosY;
    if (fullScreenFlag) {
        int textWidth = glutBitmapLength(textFont, (const unsigned char*)text.c_str());
        textPosX = (float)this->width / 2.0f - textWidth / 4.0f;
    } else {
        int textWidth = glutBitmapLength(textFont, (const unsigned char*)text.c_str());
        textPosX = (float)this->width / 2.0f - textWidth / 2.0f;
    }
    textPosY = this->height - yOffset;
    glRasterPos2f(textPosX, textPosY);
    glutBitmapString(textFont, (const unsigned char*)text.c_str());
}

void Window::drawRectangle(float x, float y, int width, int height) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    glEnd();
}

void Window::drawFilledCircle(float x, float y, int radius) {
    int triangleAmount = 15;                // number of triangles used in drawing the circle
    float twicePI = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);                   // center of the circle
        for (int i = 0; i <= triangleAmount; i++) {
            float posX = x + (radius * cos(i * twicePI / triangleAmount));
            float posY = y + (radius * sin(i * twicePI / triangleAmount));
            glVertex2f(posX, posY);
        }
    glEnd();
}

void Window::enable2D() {
    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, this->width, 0.0f, this->height, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

std::string Window::scoreToString() {
    return std::to_string(this->scoreLeft) + " : " + std::to_string(this->scoreRight);
}

void Window::toggleFullScreen(bool fullScreenFlag) {
    if (fullScreenFlag) {
        glutPositionWindow(0, 0);
        glutReshapeWindow(this->width, this->height);
    } else {
        glutFullScreen();
    }
}
