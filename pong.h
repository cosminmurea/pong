#ifndef PONG_H
#define PONG_H

#include <string>

/* The updateState function will be called every 16 milliseconds */
#define UPDATE_RATE 16

/* Converts the score to a string.
No inputs.
Outputs :
    - string score : the score represented as a string;
*/
std::string scoreToString();

/* Handles drawing to the screen. Callback for glutDisplayFunc().
No inputs.
No outputs.
*/
void drawFrame();

/* Handles ball collisions and trajectory.
No inputs.
No outputs.
*/
void updateBall();

/* Updates state and redisplays the frame every 16 milliseconds.
Callback for glutTimerFunc().
Inputs :
    - int value : mandatory argument for glutTimerFunc() callback;
No outputs.
*/
void updateState(int value);

/* Handles the movement of the paddles and other keyboard
related functionalities.
Inputs :
    - unsigned char key : the ASCII code of the pressed key;
    - int x, y : window relative coordinates of the mouse;
No outputs.
*/
void normalKeysHandler(unsigned char key, int x, int y);

/* Initializes and starts the game.
Inputs :
    - int argc : number of command line arguments;
    - char** argv : array of command line arguments;
No outputs.
*/
void run(int argc, char** argv);

#endif
