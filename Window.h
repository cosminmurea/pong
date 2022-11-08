#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window {
    int width;
    int height;

    public:

    Window(int width, int height);

    // Getters
    int getWidth();
    int getHeight();

    // Setters
    void setWidth(int width);
    void setHeight(int height);

    /*Writes a string at position (x, y).
    *Inputs :
    *   - void* textFont : a font for the drawn text;
    *   - float x, y : a position (x, y) in pixels;
    *   - string text : a string to write;
    *No outputs.
    */
    void drawText(void* textFont, float x, float y, std::string text);

    /*Computes the width of a text in pixels (based on the font).
    *Inputs :
    *   - void* textFont : the font used to write;
    *   - string text : a string to measure;
    *Outputs :
    *   - int textWidth : the width of the text in pixels;
    */
    int drawnTextWidth(void* textFont, std::string text);

    /*Draws a rectangle using OpenGL.
    *Inputs :
    *   - float x, y : the position (x, y) of the bottom left corner of the rectangle;
    *   - int width : the width of the rectangle;
    *   - int height: the height of the rectangle;
    *No outputs.
    */
    void drawRectangle(float x, float y, int width, int height);

    /*Sets up OpenGL configurations for 2D.
    *No inputs.
    *No outputs.
    */
    void enable2D();

    /* Converts the score to a string.
    *No inputs.
    *Outputs :
    *   - string score : the score represented as a string;
    */
    std::string scoreToString(int scoreLeft, int scoreRight);
};

#endif