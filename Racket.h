#ifndef RACKET_H
#define RACKET_H

#include <GL/freeglut.h>

class Racket {
    float x;
    float y;
    static const int width;
    static const int height;
    static const int speed;

    public:

    Racket(float x, float y);

    /* ----- = == === 1. GETTERS === == = ----- */

    float getX();
    float getY();
    static const int getWidth();
    static const int getHeight();
    static const int getSpeed();

    /* ----- = == === 2. SETTERS === == = ----- */

    void setX(float x);
    void setY(float y);

    /* ----- = == === 3. GRAPHICS & MOVEMENT === == = ----- */

    /**
     * @brief Handles the drawing of the rackets (filled rectangles) using GL_QUADS.
     */
    void draw();

    /**
     * @brief Handles the movement of the rackets. Racket movement is only vertical (along the Y - Axis).
     * 
     * @param moveUp        flag marking whether the racket should move up;
     * @param moveDown      flag marking whether the racket should move down;
     * @param windowHeight  height of the game window;
     */
    void move(bool moveUp, bool moveDown, int windowHeight);
};

#endif
