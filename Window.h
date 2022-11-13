#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window {
    int width;
    int height;
    int scoreLeft;
    int scoreRight;
    static const int updateRate;

    public:

    Window(int width, int height);

    // Getters
    int getWidth();
    int getHeight();
    int getScoreLeft();
    int getScoreRight();
    static const int getUpdateRate();

    // Setters
    void setWidth(int width);
    void setHeight(int height);
    void setScoreLeft(int scoreLeft);
    void setScoreRight(int scoreRight);

    void drawHCenteredText(void* textFont, int yOffset, std::string text, bool fullScreenFlag);

    /*Draws a rectangle using OpenGL.
    *Inputs :
    *   - float x, y : the position (x, y) of the bottom left corner of the rectangle;
    *   - int width : the width of the rectangle;
    *   - int height: the height of the rectangle;
    *No outputs.
    */
    void drawRectangle(float x, float y, int width, int height);

    void drawFilledCircle(float x, float y, int radius);

    /*Sets up OpenGL configurations for 2D.
    *No inputs.
    *No outputs.
    */
    void enable2D();

    void toggleFullScreen(bool fullScreenFlag);

    /* Converts the score to a string.
    *No inputs.
    *Outputs :
    *   - string score : the score represented as a string;
    */
    std::string scoreToString();
};

#endif