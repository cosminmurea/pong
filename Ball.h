#ifndef BALL_H
#define BALL_H

class Ball {
    float posX;
    float posY;
    float dirX;
    float dirY;
    static const int size;
    static const int speed;

    public:

    Ball(float posX, float posY, float dirX, float dirY);

    // Getters
    float getPosX();
    float getPosY();
    float getDirX();
    float getDirY();
    static const int getSize();
    static const int getSpeed();

    // Setters
    void setPosX(float posX);
    void setPosY(float posY);
    void setDirX(float dirX);
    void setDirY(float dirY);

    /*Normalizes a vector with two components.
    *No inputs.
    *No outputs.
    */
    void normalizeVector();
};

#endif