#ifndef BALL_H
#define BALL_H

#include <GL/freeglut.h>
#include <cmath>

class Ball {
    float posX;
    float posY;
    float dirX;
    float dirY;
    static const int speed;
    static const int size;

    public:

    Ball(float posX, float posY, float dirX, float dirY);

    /* ----- = == === 1. GETTERS === == = ----- */

    float getPosX();
    float getPosY();
    float getDirX();
    float getDirY();
    static const int getSpeed();
    static const int getSize();

    /* ----- = == === 2. SETTERS === == = ----- */

    void setPosX(float posX);
    void setPosY(float posY);
    void setDirX(float dirX);
    void setDirY(float dirY);

    /* ----- = == === 3. GRAPHICS & MOVEMENT === == = ----- */

    /**
     * @brief Handles the drawing of the ball (a filled circle) using GL_TRIANGLE_FAN.
     */
    void draw();

    /**
     * @brief Handles the movement of the ball as well as collisions between the ball, rackets and borders.
     *
     * @param scoreLeft     reference to the left score;
     * @param scoreRight    reference to the right score;
     * @param racketLeftX   X coordinate of the left racket;
     * @param racketLeftY   Y coordinate of the left racket;
     * @param racketRightX  X coordinate of the right racket;
     * @param racketRightY  Y coordinate of the right racket;
     * @param racketWidth   width of the racket;
     * @param racketHeight  height of the racket;
     * @param windowWidth   width of the game window;
     * @param windowHeight  height of the game window;
     */
    void move(
        int& scoreLeft,
        int& scoreRight,
        float racketLeftX,
        float racketLeftY,
        float racketRightX,
        float racketRightY,
        const int racketWidth,
        const int racketHeight,
        int windowWidth,
        int windowHeight
    );

    /**
     * @brief Handles the normalization of the ball direction vector.
     * Computes the magnitude of the vector then multiplies each component with the inversed magnitude.
     */
    void normalizeVector();
};

#endif
