#include "Window.h"
#include <GL/freeglut.h>
#include <cmath>

// The 'this' keyword is only used when needed (eg. parameters named the same as the data members).

const int Window::updateRate = 1000 / 60;

Window::Window(int width, int height) {
    this->width = width;
    this->height = height;
    scoreLeft = 0;
    scoreRight = 0;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

int Window::getScoreLeft() {
    return scoreLeft;
}

int Window::getScoreRight() {
    return scoreRight;
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
        textPosX = (float)width / 2.0f - textWidth / 4.0f;
    } else {
        int textWidth = glutBitmapLength(textFont, (const unsigned char*)text.c_str());
        textPosX = (float)width / 2.0f - textWidth / 2.0f;
    }
    textPosY = height - yOffset;
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
    int triangleAmount = 18;                // number of triangles used in drawing the circle
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
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

std::string Window::scoreToString() {
    return std::to_string(scoreLeft) + " : " + std::to_string(scoreRight);
}

void Window::toggleFullScreen(bool fullScreenFlag) {
    if (fullScreenFlag) {
        glutPositionWindow(0, 0);
        glutReshapeWindow(width, height);
    } else {
        glutFullScreen();
    }
}
