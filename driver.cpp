#include "Game.h"
#include <GL/freeglut.h>

Game pong;

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

/*Updates state and redisplays the frame every 16 milliseconds. Callback for glutTimerFunc().
*Inputs :
*   - int value : mandatory argument for glutTimerFunc() callback;
*No outputs.
*/
void updateState(int value) {
    if (pong.getPaused()) {
        // Menu logic
    } else {
        // Game logic
        pong.moveRackets();
        pong.moveBall();
    }

    glutTimerFunc(Window::getUpdateRate(), updateState, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(pong.window.getWidth(), pong.window.getHeight());
    glutCreateWindow("GLUT Pong");
    glutSetCursor(GLUT_CURSOR_NONE);
    glutIgnoreKeyRepeat(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    pong.window.enable2D();

    glutDisplayFunc(drawFrameWrapper);
    glutKeyboardFunc(handleKeyDownWrapper);
    glutKeyboardUpFunc(handleKeyUpWrapper);
    glutTimerFunc(Window::getUpdateRate(), updateState, 0);

    glutMainLoop();

    return 0;
}
