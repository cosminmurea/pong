#include "Window.h"                     // also includes <string>
#include "Racket.h"
#include "Ball.h"
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

// Game control keys: W - 0, S - 1, I - 2, K - 3
bool gameCtrlKeys[4] = {false};
// F - toggle full-screen mode
bool fullScreen = false;
// P - pause the game
bool paused = false;

Window window(1000, 500);
Racket racketLeft(10.0f, window.getHeight() / 2 - Racket::getHeight() / 2);
Racket racketRight(window.getWidth() - Racket::getWidth() - 10, window.getHeight() / 2 - Racket::getHeight() / 2);
Ball ball(window.getWidth() / 2, window.getHeight() / 2, -1.0f, 0.0f);

/*Handles drawing to the screen. Callback for glutDisplayFunc().
*No inputs.
*No outputs.
*/
void drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (paused) {
        // Draw the menu
        window.drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 200, "P - Resume Game", fullScreen);
        window.drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 240, "F - Full Screen Mode", fullScreen);
        window.drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 280, "Esc - Quit Game", fullScreen);
    } else {
        // Draw the game
        window.drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 20, window.scoreToString(), fullScreen);
        window.drawRectangle(racketLeft.getX(), racketLeft.getY(), Racket::getWidth(), Racket::getHeight());
        window.drawRectangle(racketRight.getX(), racketRight.getY(), Racket::getWidth(), Racket::getHeight());
        window.drawFilledCircle(ball.getPosX(), ball.getPosY(), Ball::getSize());
    }

    glutSwapBuffers();
}

void handleKeyDown(unsigned char key, int x, int y) {
    if (paused) {
    } else {
        // Keyboard handler for the game
        if (key == 119) {
            gameCtrlKeys[0] = true;
        }
        if (key == 115) {
            gameCtrlKeys[1] = true;
        }
        if (key == 105) {
            gameCtrlKeys[2] = true;
        }
        if (key == 107) {
            gameCtrlKeys[3] = true;
        }
    }

    // Keys that work in both the 'game' and 'menu' states
    if (key == 27) {
        exit(0);
    }
    if (key == 102) {
        window.toggleFullScreen(fullScreen);
        fullScreen = !fullScreen;
    }
    if (key == 112) {
        paused = !paused;
    }
}

void handleKeyUp(unsigned char key, int x, int y) {
    if (key == 119) {
        gameCtrlKeys[0] = false;
    }
    if (key == 115) {
        gameCtrlKeys[1] = false;
    }
    if (key == 105) {
        gameCtrlKeys[2] = false;
    }
    if (key == 107) {
        gameCtrlKeys[3] = false;
    }
}

/*Handles the movement of the paddles and other keyboard related functionalities.
*Inputs :
*   - unsigned char key : the ASCII code of the pressed key;
*   - int x, y : window relative coordinates of the mouse;
*No outputs.
*/
void moveRacket() {
    if ((gameCtrlKeys[0]) && (racketLeft.getY() < window.getHeight() - Racket::getHeight() - 10)) {
        racketLeft.setY(racketLeft.getY() + Racket::getSpeed());
    }
    if ((gameCtrlKeys[1]) && (racketLeft.getY() > 10)) {
        racketLeft.setY(racketLeft.getY() - Racket::getSpeed());
    }
    if ((gameCtrlKeys[2]) && (racketRight.getY() < window.getHeight() - Racket::getHeight() - 10)) {
        racketRight.setY(racketRight.getY() + Racket::getSpeed());
    }
    if ((gameCtrlKeys[3]) && (racketRight.getY() > 10)) {
        racketRight.setY(racketRight.getY() - Racket::getSpeed());
    }
}

/*Handles ball collisions and trajectory.
*No inputs.
*No outputs.
*/
void moveBall() {
    // Start by flying straight to the left.
    ball.setPosX(ball.getPosX() + (ball.getDirX() * Ball::getSpeed()));
    ball.setPosY(ball.getPosY() + (ball.getDirY() * Ball::getSpeed()));

    // Collisions
    //  1. Top border
    if (ball.getPosY() > window.getHeight() - Ball::getSize() - 10) {
        ball.setDirY(-fabs(ball.getDirY()));
    }
    //  2. Bottom border
    if (ball.getPosY() < Ball::getSize() + 10) {
        ball.setDirY(fabs(ball.getDirY()));
    }
    //  3. Left border
    if (ball.getPosX() < Ball::getSize()) {
        window.setScoreRight(window.getScoreRight() + 1);
        ball.setPosX(window.getWidth() / 2);
        ball.setPosY(window.getHeight() / 2);
        ball.setDirX(fabs(ball.getDirX()));
        ball.setDirY(0);
    }
    //  4. Right border
    if (ball.getPosX() > window.getWidth() - Ball::getSize()) {
        window.setScoreLeft(window.getScoreLeft() + 1);
        ball.setPosX(window.getWidth() / 2);
        ball.setPosY(window.getHeight() / 2);
        ball.setDirX(-fabs(ball.getDirX()));
        ball.setDirY(0);
    }
    //  5. Left racket
    if ((ball.getPosX() <= racketLeft.getX() + Racket::getWidth() + Ball::getSize()) &&
        (ball.getPosY() <= racketLeft.getY() + Racket::getHeight() + Ball::getSize()) &&
        (ball.getPosY() >= racketLeft.getY() - Ball::getSize())) {
        ball.setDirX(fabs(ball.getDirX()));
        // Changes the trajectory of the ball based on where it collided with the racket.
        // It takes a value between [-0.5, 0.5] : 0.5 if it hits the top of the paddle and -0.5 for the bottom.
        float trajChange = (ball.getPosY() - racketLeft.getY()) / Racket::getHeight() - 0.5f;
        ball.setDirY(trajChange);
    }
    //  6. Right racket
    if ((ball.getPosX() >= racketRight.getX() - Ball::getSize()) &&
        (ball.getPosY() <= racketRight.getY() + Racket::getHeight() + Ball::getSize()) &&
        (ball.getPosY() >= racketRight.getY() - Ball::getSize())) {
        ball.setDirX(-fabs(ball.getDirX()));
        float trajChange = (ball.getPosY() - racketRight.getY()) / Racket::getHeight() - 0.5f;
        ball.setDirY(trajChange);
    }

    //ball.normalizeVector();
}

/*Updates state and redisplays the frame every 16 milliseconds. Callback for glutTimerFunc().
*Inputs :
*   - int value : mandatory argument for glutTimerFunc() callback;
*No outputs.
*/
void updateState(int value) {
    if (paused) {
        // Menu logic
    } else {
        // Game logic
        moveRacket();
        moveBall();
    }

    glutTimerFunc(Window::getUpdateRate(), updateState, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(window.getWidth(), window.getHeight());
    glutCreateWindow("GLUT Pong");
    glutSetCursor(GLUT_CURSOR_NONE);
    glutIgnoreKeyRepeat(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    window.enable2D();

    glutDisplayFunc(drawFrame);
    glutKeyboardFunc(handleKeyDown);
    glutKeyboardUpFunc(handleKeyUp);
    glutTimerFunc(Window::getUpdateRate(), updateState, 0);

    glutMainLoop();

    return 0;
}
