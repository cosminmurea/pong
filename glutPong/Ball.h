#ifndef BALL_H
#define BALL_H

class Ball {
    float posX;
    float posY;
    float dirX;
    float dirY;
    static const int speed;
    static const int size;

    public:

    Ball(float posX, float posY, float dirX, float dirY);

    // Getters
    float getPosX();
    float getPosY();
    float getDirX();
    float getDirY();
    static const int getSpeed();
    static const int getSize();

    // Setters
    void setPosX(float posX);
    void setPosY(float posY);
    void setDirX(float dirX);
    void setDirY(float dirY);

    /*Handles the normalization of the ball direction vector.
    *First compute the magnitude of the vector then divide each component by the magnitude.
    *No inputs.
    *No outputs.
    */
    void normalizeVector();
};

#endif
