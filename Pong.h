#ifndef PONG_H
#define PONG_H

#include "Racket.h"
#include "Ball.h"
#include <GL/freeglut.h>
#include <cmath>
#include <string>
#include <iostream>

class Pong {
    int width;
    int height;
    int scoreLeft;
    int scoreRight;
    bool gameCtrlKeys[4];
    bool isPaused;
    bool isFullScreen;
    bool xModeEnabled;
    static const int updateRate;

    Racket racketLeft;
    Racket racketRight;
    Ball ball;

    public:

    Pong(int width, int height);

    /* ----- = == === 1. GETTERS === == = ----- */

    int getWidth();
    int getHeight();
    bool getIsPaused();
    bool getXModeEnabled();
    static const int getUpdateRate();

    /* ----- = == === 2. SETTERS === == = ----- */

    void setIsPaused(bool isPaused);

    /* ----- = == === 3. GRAPHICS === == = ----- */

    /**
     * @brief Sets up OpenGL orthographic projection for 2D.
     */
    void init2D();

    /**
     * @brief Draw horizontally centered text at a given Y - Axis offset.
     * 
     * @param textFont  font supported by glutBitmapString();
     * @param yOffset   offset along the Y - Axis (yOffset = 0 => top of the window);
     * @param text      text to be drawn on screen;
     */
    void drawHCenteredText(void* textFont, int yOffset, std::string text);

    /**
     * @brief Switches between normal and full screen mode.
     */
    void toggleFullScreen();

    /**
     * @brief Handles the drawing of the game scene, the pause scene and the game won scene.
     * The game scene is drawn using only methods of the Racket and Ball objects.
     */
    void drawFrame();

    /* ----- = == === 4. KEYBOARD INPUT === == = ----- */

    /**
     * @brief Handles keyboard input for the game menu keys as well as ONLY key PRESSES for the game control keys.
     * 
     * @param key   the ASCII code of the pressed key;
     * @param x     X coordinate of the cursor when pressing the key;
     * @param y     Y coordinate of the cursor when pressing the key;
     */
    void handleKeyDown(unsigned char key, int x, int y);

    /**
     * @brief Handles ONLY key RELEASES for the game control keys;
     * 
     * @param key   the ASCII code of the pressed key;
     * @param x     X coordinate of the cursor when pressing the key;
     * @param y     Y coordinate of the cursor when pressing the key;
     */
    void handleKeyUp(unsigned char key, int x, int y);

    /* ----- = == === 5. GAME LOGIC === == = ----- */

    /**
     * @brief Wraps the calls to the move() method of the Racket class.
     */
    void moveRackets();

    /**
     * @brief Wraps a call to the move() method of the Ball class.
     */
    void moveBall();

    /**
     * @brief Resets the score, the position of the rackets and the position and direction of the ball.
     */
    void resetGame();

    /**
     * @brief Switches between endless and X mode.
     */
    void toggleXMode();

    /**
     * @brief Checks if the game has ended.
     * 
     * @return true if one of the players reached the necessary number of goals;
     * @return false if no player reached the necessary number of goals;
     */
    bool gameEnded();

    /**
     * @brief Create a message congratulating the winner (left or right).
     * 
     * @return std::string a message congratulating the winner;
     */
    std::string gameWonMessage();

    /**
     * @brief Turn the two score variables into a string (separated by " : ").
     * 
     * @return std::string the score in text form;
     */
    std::string scoreToString();
};

#endif
