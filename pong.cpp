#include "pong.h"
#include <GL/freeglut.h>

int scoreRight = 0;
int scoreLeft = 0;

float racketLeftX = 10.0f;
float racketLeftY = WINDOW_HEIGHT / 2 - RACKET_HEIGHT / 2;
float racketRightX = WINDOW_WIDTH - RACKET_WIDTH - 10;
float racketRightY = WINDOW_HEIGHT / 2 - RACKET_HEIGHT / 2;

float ballPositionX = WINDOW_WIDTH / 2;
float ballPositionY = WINDOW_HEIGHT / 2;
float ballDirectionX = 0.0f;
float ballDirectionY = -1.0f;
int ballSize = 10;
int ballSpeed = 5;

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

int drawnTextWidth(void* textFont, std::string text) {
    int textWidth = 0;

    for(unsigned int i = 0; i < text.length(); i++) {
        textWidth += glutBitmapWidth(textFont, text[i]);
    }

    return textWidth;
}

std::string scoreToString() {
    return std::to_string(scoreLeft) + " : " + std::to_string(scoreRight);
}

void drawRectangle(float x, float y, int width, int height) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    glEnd();
}

void drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    int scoreTextWidth = drawnTextWidth(GLUT_BITMAP_8_BY_13, scoreToString());              // used to help center the text
    drawText(WINDOW_WIDTH / 2 - scoreTextWidth / 2, WINDOW_HEIGHT - 20, scoreToString());

    drawRectangle(racketLeftX, racketLeftY, RACKET_WIDTH, RACKET_HEIGHT);
    drawRectangle(racketRightX, racketRightY, RACKET_WIDTH, RACKET_HEIGHT);
    drawRectangle(ballPositionX - ballSize / 2, ballPositionY - ballSize / 2, ballSize, ballSize);

    glutSwapBuffers();
}

void updateBall() {
    if (ballPositionY > 10) {
        ballPositionX += ballDirectionX * ballSpeed;
        ballPositionY += ballDirectionY * ballSpeed;
    }
}

void updateState(int value) {
    updateBall();
    glutTimerFunc(UPDATE_RATE, updateState, 0);
    glutPostRedisplay();
}

void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void normalKeysHandler(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    if ((key == 119) && (racketLeftY < WINDOW_HEIGHT - RACKET_HEIGHT - 10)) {
        racketLeftY += RACKET_SPEED;
    }

    if ((key == 115) && (racketLeftY > 10)) {
        racketLeftY -= RACKET_SPEED;
    }

    if ((key == 105) && (racketRightY < WINDOW_HEIGHT - RACKET_HEIGHT - 10)) {
        racketRightY += RACKET_SPEED;
    }

    if ((key == 107) && (racketRightY > 10)) {
        racketRightY -= RACKET_SPEED;
    }

    glutPostRedisplay();
}

void run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GLUT Pong");

    // Register callbacks.
    glutDisplayFunc(drawFrame);
    glutKeyboardFunc(normalKeysHandler);
    glutTimerFunc(UPDATE_RATE, updateState, 0);

    // Enable 2D and set draw color to white.
    enable2D(WINDOW_WIDTH, WINDOW_HEIGHT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glutMainLoop();
}
