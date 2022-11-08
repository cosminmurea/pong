#include "Window.h"         // also includes <string>
#include "Racket.h"
#include "Ball.h"
#include <GL/freeglut.h>
#include <cmath>

int updateRate = 16;
int scoreLeft = 0;
int scoreRight = 0;

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

    int scoreTextWidth = window.drawnTextWidth(GLUT_BITMAP_8_BY_13, window.scoreToString(scoreLeft, scoreRight));
    window.drawText(GLUT_BITMAP_8_BY_13, window.getWidth() / 2 - scoreTextWidth / 2, window.getHeight() - 20, window.scoreToString(scoreLeft, scoreRight));

    window.drawRectangle(racketLeft.getX(), racketLeft.getY(), Racket::getWidth(), Racket::getHeight());
    window.drawRectangle(racketRight.getX(), racketRight.getY(), Racket::getWidth(), Racket::getHeight());
    window.drawRectangle(ball.getPosX() - Ball::getSize() / 2, ball.getPosY() - Ball::getSize() / 2, Ball::getSize(), Ball::getSize());

    glutSwapBuffers();
}

/*Handles the movement of the paddles and other keyboard related functionalities.
*Inputs :
*   - unsigned char key : the ASCII code of the pressed key;
*   - int x, y : window relative coordinates of the mouse;
*No outputs.
*/
void normalKeysHandler(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    if ((key == 119) && (racketLeft.getY() < window.getHeight() - Racket::getHeight() - 10)) {
        racketLeft.setY(racketLeft.getY() + Racket::getSpeed());
    }

    if ((key == 115) && (racketLeft.getY() > 10)) {
        racketLeft.setY(racketLeft.getY() - Racket::getSpeed());
    }

    if ((key == 105) && (racketRight.getY() < window.getHeight() - Racket::getHeight() - 10)) {
        racketRight.setY(racketRight.getY() + Racket::getSpeed());
    }

    if ((key == 107) && (racketRight.getY() > 10)) {
        racketRight.setY(racketRight.getY() - Racket::getSpeed());
    }

    glutPostRedisplay();
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
        ++scoreRight;
        ball.setPosX(window.getWidth() / 2);
        ball.setPosY(window.getHeight() / 2);
        ball.setDirX(fabs(ball.getDirX()));
        ball.setDirY(0);
    }
    //  4. Right border
    if (ball.getPosX() > window.getWidth() - Ball::getSize()) {
        ++scoreLeft;
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

    ball.normalizeVector();
}

/*Updates state and redisplays the frame every 16 milliseconds. Callback for glutTimerFunc().
*Inputs :
*   - int value : mandatory argument for glutTimerFunc() callback;
*No outputs.
*/
void updateState(int value) {
    moveBall();
    glutTimerFunc(updateRate, updateState, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window.getWidth(), window.getHeight());
    glutCreateWindow("GLUT Pong");
    glColor3f(1.0f, 1.0f, 1.0f);
    window.enable2D();

    glutDisplayFunc(drawFrame);
    glutKeyboardFunc(normalKeysHandler);
    glutTimerFunc(updateRate, updateState, 0);

    glutMainLoop();

    return 0;
}
