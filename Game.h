#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Racket.h"
#include "Ball.h"

class Game {
    // Game control keys: W - 0, S - 1, I - 2, K - 3
    bool gameCtrlKeys[4];
    // F - toggle full-screen mode
    bool fullScreen;
    // P - pause the game
    bool paused;
    // X - enable first-to mode
    bool xMode;

    public:

    Window window;
    Racket racketLeft;
    Racket racketRight;
    Ball ball;

    Game();

    // Getters
    bool getPaused();
    bool getXMode();

    // Setters
    void setPaused(bool paused);
    void setXMode(bool xMode);

    /*Checks if the game has been won or not.
    *No inputs.
    *Outputs :
    *   - bool gameWon : represents the state of the game in xMode (won or ongoing);
    */
    bool gameWon();

    /*Compares the scores and returns an appropriate winning message.
    *No inputs.
    *Outputs :
    *   - string winner : winning message (for xMode only);
    */
    std::string whoWon();

    /*Handles drawing to the screen. Callback for glutDisplayFunc().
    *No inputs.
    *No outputs.
    */
    void drawFrame();

    /*Handles the key presses for BOTH game control keys and menu control keys.
    *Inputs :
    *   - unsigned char key : the ASCII code of the pressed key;
    *   - int x, y : window relative coordinates of the mouse;
    *No outputs.
    */
    void handleKeyDown(unsigned char key, int x, int y);

    /*Handles the key releases for ONLY the game control keys.
    *Inputs :
    *   - unsigned char key : the ASCII code of the pressed key;
    *   - int x, y : window relative coordinates of the mouse;
    *No outputs.
    */
    void handleKeyUp(unsigned char key, int x, int y);

    /*Reset the score, the position of the rackets and the position and direction of the ball.
    *No inputs.
    *No outputs.
    */
    void newGame();

    /*Handles the movement of the paddles.
    *No inputs.
    *No outputs.
    */
    void moveRackets();

    /*Handles ball collisions and trajectory.
    *No inputs.
    *No outputs.
    */
    void moveBall();
};

#endif
