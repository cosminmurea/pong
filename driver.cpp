#include "Pong.h"

Pong pong(1000, 500);

// GLUT does not accept member functions as callbacks
// => every member function is wrapped and the wrapper function is passed as the callback.

void drawFrameWrapper() {
    pong.drawFrame();
}

void handleKeyDownWrapper(unsigned char key, int x, int y) {
    pong.handleKeyDown(key, x, y);
}

void handleKeyUpWrapper(unsigned char key, int x, int y) {
    pong.handleKeyUp(key, x, y);
}

/**
 * @brief Updates the internal state of the game and redisplays the frame every 16 milliseconds.
 * 
 * @param value required by freeglut;
 */
void updateState(int value) {
    if (pong.getIsPaused()) {
        // Menu logic
    } else {
        // Game logic
        if (pong.getXModeEnabled()) {
            if (pong.gameEnded()) {
                pong.setIsPaused(true);
            }
        }
        pong.moveRackets();
        pong.moveBall();
    }

    glutTimerFunc(Pong::getUpdateRate(), updateState, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(pong.getWidth(), pong.getHeight());
    glutCreateWindow("GLUT Pong");
    glutSetCursor(GLUT_CURSOR_NONE);
    glutIgnoreKeyRepeat(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    pong.init2D();

    glutDisplayFunc(drawFrameWrapper);
    glutKeyboardFunc(handleKeyDownWrapper);
    glutKeyboardUpFunc(handleKeyUpWrapper);
    glutTimerFunc(Pong::getUpdateRate(), updateState, 0);

    glutMainLoop();

    return 0;
}
