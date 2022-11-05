#include "pong.h"
#include "Racket.h"
#include <GL/freeglut.h>
#include <cmath>

/*
Class structure :
    1. class Racket
        - data : racketX, racketY, RACKET_WIDTH, RACKET_HEIGHT, RACKET_SPEED
    2. class Ball
        - data : ballPositionX, ballPositionY, ballDirectionX, ballDirectionY, BALL_SIZE, BALL_SPEED
        - methods : updateBall(), normalizeVector()
    3. class GameEngine
        - data : WINDOW_WIDTH, WINDOW_HEIGHT, UPDATE_RATE, scoreRight, scoreLeft
        - methods : drawText(), drawnTextWidth(), scoreToString(), drawRectangle(), drawFrame(), updateState(), enable2D(), run()
*/

int scoreRight = 0;
int scoreLeft = 0;

Racket racketLeft(10.0f, WINDOW_HEIGHT / 2 - Racket::getHeight() / 2);
Racket racketRight(WINDOW_WIDTH - Racket::getWidth() - 10, WINDOW_HEIGHT / 2 - Racket::getHeight() / 2);

float ballPositionX = WINDOW_WIDTH / 2;
float ballPositionY = WINDOW_HEIGHT / 2;
float ballDirectionX = -1.0f;
float ballDirectionY = 0.0f;

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

    drawRectangle(racketLeft.getX(), racketLeft.getY(), Racket::getWidth(), Racket::getHeight());
    drawRectangle(racketRight.getX(), racketRight.getY(), Racket::getWidth(), Racket::getHeight());
    drawRectangle(ballPositionX - BALL_SIZE / 2, ballPositionY - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE);

    glutSwapBuffers();
}

void normalizeVector(float& x, float& y) {
    float magnitude = sqrt((x * x) + (y * y));
    if (magnitude != 0.0f) {
        magnitude = 1.0f / magnitude;
        x *= magnitude;
        y *= magnitude;
    }
}

void updateBall() {
    // Start by flying straight to the left.
    ballPositionX += ballDirectionX * BALL_SPEED;
    ballPositionY += ballDirectionY * BALL_SPEED;

    // Collisions
    //  1. Top border
    if (ballPositionY > WINDOW_HEIGHT - BALL_SIZE - 10) {
        ballDirectionY = -fabs(ballDirectionY);
    }
    //  2. Bottom border
    if (ballPositionY < BALL_SIZE + 10) {
        ballDirectionY = fabs(ballDirectionY);
    }
    //  3. Left border
    if (ballPositionX < BALL_SIZE) {
        ++scoreRight;
        ballPositionX = WINDOW_WIDTH / 2;
        ballPositionY = WINDOW_HEIGHT / 2;
        ballDirectionX = fabs(ballDirectionX);
        ballDirectionY = 0;
    }
    //  4. Right border
    if (ballPositionX > WINDOW_WIDTH - BALL_SIZE) {
        ++scoreLeft;
        ballPositionX = WINDOW_WIDTH / 2;
        ballPositionY = WINDOW_HEIGHT / 2;
        ballDirectionX = -fabs(ballDirectionX);
        ballDirectionY = 0;
    }
    //  5. Left racket
    if ((ballPositionX <= racketLeft.getX() + Racket::getWidth() + BALL_SIZE) &&
        (ballPositionY <= racketLeft.getY() + Racket::getHeight() + BALL_SIZE) &&
        (ballPositionY >= racketLeft.getY() - BALL_SIZE)) {
        // 0.5 for top hit, 0 for center hit, -0.5 for bottom hit
        ballDirectionX = fabs(ballDirectionX);
        ballDirectionY = ((ballPositionY - racketLeft.getY()) / Racket::getHeight()) - 0.5f;
    }
    //  6. Right racket
    if ((ballPositionX >= racketRight.getX() - BALL_SIZE) &&
        (ballPositionY <= racketRight.getY() + Racket::getHeight() + BALL_SIZE) &&
        (ballPositionY >= racketRight.getY() - BALL_SIZE)) {
        ballDirectionX = -fabs(ballDirectionX);
        ballDirectionY = ((ballPositionY - racketRight.getY()) / Racket::getHeight()) - 0.5f;
    }

    normalizeVector(ballDirectionX, ballDirectionY);
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

    if ((key == 119) && (racketLeft.getY() < WINDOW_HEIGHT - Racket::getHeight() - 10)) {
        racketLeft.setY(racketLeft.getY() + Racket::getSpeed());
    }

    if ((key == 115) && (racketLeft.getY() > 10)) {
        racketLeft.setY(racketLeft.getY() - Racket::getSpeed());
    }

    if ((key == 105) && (racketRight.getY() < WINDOW_HEIGHT - Racket::getHeight() - 10)) {
        racketRight.setY(racketRight.getY() + Racket::getSpeed());
    }

    if ((key == 107) && (racketRight.getY() > 10)) {
        racketRight.setY(racketRight.getY() - Racket::getSpeed());
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
