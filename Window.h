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

    /*Draw horizontally centered text on the screen.
    *Inputs :
    *   - void* textFont : the GLUT font used to draw the text;
    *   - int yOffset : the y-Axis offset from the top of the screen;
    *   - string text : string of text to be drawn;
    *   - bool fullScreenFlag : used check if full screen mode is enabled;
    */
    void drawHCenteredText(void* textFont, int yOffset, std::string text, bool fullScreenFlag);

    /*Draws a rectangle using OpenGL.
    *Inputs :
    *   - float x, y : the position (x, y) of the bottom left corner of the rectangle;
    *   - int width : the width of the rectangle;
    *   - int height: the height of the rectangle;
    *No outputs.
    */
    void drawRectangle(float x, float y, int width, int height);

    /*Draws a filled circle using OpenGL.
    *Inputs :
    *   - float x, y : the position (x, y) of the center of the circle;
    *   - int radius : the radius of the circle;
    *No outputs.
    */
    void drawFilledCircle(float x, float y, int radius);

    /*Sets up OpenGL orthographic projection for 2D.
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
