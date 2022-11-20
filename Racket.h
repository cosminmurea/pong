#ifndef RACKET_H
#define RACKET_H

class Racket {
    float x;
    float y;
    static const int width;
    static const int height;
    static const int speed;

    public:

    Racket(float x, float y);

    // Getters
    float getX();
    float getY();
    static const int getWidth();
    static const int getHeight();
    static const int getSpeed();

    // Setters
    void setX(float x);
    void setY(float y);
};

#endif
