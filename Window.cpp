#include "Window.h"
#include <GL/freeglut.h>

Window::Window(int width, int height) {
    this->width = width;
    this->height = height;
}

int Window::getWidth() {
    return this->width;
}

int Window::getHeight() {
    return this->height;
}

void Window::setWidth(int width) {
    this->width = width;
}

void Window::setHeight(int height) {
    this->height = height;
}

void Window::drawText(void* textFont, float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glutBitmapString(textFont, (const unsigned char*)text.c_str());
}

int Window::drawnTextWidth(void* textFont, std::string text) {
    int textWidth = 0;

    for(unsigned int i = 0; i < text.length(); i++) {
        textWidth += glutBitmapWidth(textFont, text[i]);
    }

    return textWidth;
}

void Window::drawRectangle(float x, float y, int width, int height) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    glEnd();
}

void Window::enable2D() {
    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, this->width, 0.0f, this->height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

std::string Window::scoreToString(int scoreLeft, int scoreRight) {
    return std::to_string(scoreLeft) + " : " + std::to_string(scoreRight);
}
