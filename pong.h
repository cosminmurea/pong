#ifndef PONG_H
#define PONG_H

#include <string>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

/* The updateState function will be called every 16 milliseconds */
#define UPDATE_RATE 16

#define RACKET_WIDTH 10
#define RACKET_HEIGHT 100
#define RACKET_SPEED 8

#define BALL_SIZE 10
#define BALL_SPEED 2

/* Writes a string at position (x, y).
Inputs :
    - float x, y : a position (x, y) in pixels;
    - string text : a string to write;
No outputs.
*/
void drawText(float x, float y, std::string text);

/* Computes the width of a text in pixels (based on the font).
Inputs :
    - void* textFont : the font used to write;
    - string text : a string to measure;
Outputs :
    - int textWidth : the width of the text in pixels;
*/
int drawnTextWidth(void* textFont, std::string text);

/* Converts the score to a string.
No inputs.
Outputs :
    - string score : the score represented as a string;
*/
std::string scoreToString();

/* Draws a rectangle using OpenGL.
Inputs :
    - float x, y : the position (x, y) of the bottom left corner of the rectangle;
    - int width : the width of the rectangle;
    - int height: the height of the rectangle;
No outputs.
*/
void drawRectangle(float x, float y, int width, int height);

/* Handles drawing to the screen. Callback for glutDisplayFunc().
No inputs.
No outputs.
*/
void drawFrame();

/* Updates state and redisplays the frame every 16 milliseconds.
Callback for glutTimerFunc().
Inputs :
    - int value : mandatory argument for glutTimerFunc() callback;
No outputs.
*/
void updateState(int value);

/* Sets up OpenGL configurations for 2D.
Inputs :
    - int width : the orthographic width;
    - int height : the orthographic height;
No outputs.
*/
void enable2D(int width, int height);

/**/
void normalKeysHandler(unsigned char key, int x, int y);

/* Initializes and starts the game.
Inputs :
    - int argc : number of command line arguments;
    - char** argv : array of command line arguments;
No outputs.
*/
void run(int argc, char** argv);

#endif
