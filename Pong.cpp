#include "Pong.h"

const int Pong::updateRate = 1000 / 60;

Pong::Pong(int width, int height) :
racketLeft(10.0f, height / 2.0f - Racket::getHeight() / 2.0f),
racketRight(width - Racket::getWidth() - 10.0f, height / 2.0f - Racket::getHeight() / 2.0f),
ball(width / 2.0f, height / 2.0f, -1.0f, 0.0f) {
    this->width = width;
    this->height = height;
    scoreLeft = 0;
    scoreRight = 0;
    isPaused = false;
    xModeEnabled = false;

    for (int i = 0; i < 4; i++) {
        gameCtrlKeys[i] = false;
    }
}

int Pong::getWidth() {
    return width;
}

int Pong::getHeight() {
    return height;
}

bool Pong::getIsPaused() {
    return isPaused;
}

bool Pong::getXModeEnabled() {
    return xModeEnabled;
}

const int Pong::getUpdateRate() {
    return updateRate;
}

void Pong::setIsPaused(bool isPaused) {
    this->isPaused = isPaused;
}

void Pong::init2D() {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Pong::drawHCenteredText(void* textFont, int yOffset, std::string text) {
    float screenViewportRatio = (float)glutGet(GLUT_SCREEN_WIDTH) / width;
    float textWidth = (float)glutBitmapLength(textFont, (const unsigned char*)text.c_str());
    float textPosX;
    float textPosY = height - yOffset;

    if (isFullScreen) {
        textPosX = (float)width / 2 - textWidth / (2 * screenViewportRatio);
    } else {
        textPosX = (float)width / 2 - textWidth / 2;
    }

    glRasterPos2f(textPosX, textPosY);
    glutBitmapString(textFont, (const unsigned char*)text.c_str());
}

void Pong::toggleFullScreen() {
    if (isFullScreen) {
        glutPositionWindow(0, 0);
        glutReshapeWindow(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
    } else {
        glutFullScreen();
    }

    isFullScreen = !isFullScreen;
}

void Pong::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 30, scoreToString());

    if (isPaused) {
        if (xModeEnabled && gameEnded()) {
            // Draw the winning screen for X-Mode
            glColor3f(1.0f, 0.0f, 0.0f);
            drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 100, gameWonMessage());
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 200, "R - Resume Game");
        drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 240, "N - New Game");
        drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 280, "X - First to 10 Mode");
        drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 320, "F - Full Screen Mode");
        drawHCenteredText(GLUT_BITMAP_HELVETICA_18, 360, "Esc - Quit Game");
    } else {
        racketLeft.draw();
        racketRight.draw();
        ball.draw();
    }

    glutSwapBuffers();
}

void Pong::handleKeyDown(unsigned char key, int x, int y) {
    if (isPaused) {
        // Keyboard handler for the menu
        if (key == 110) {
            resetGame();
        }
        if (key == 120) {
            toggleXMode();
        }
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
        toggleFullScreen();
    }
    if (key == 114) {
        isPaused = !isPaused;
    }
}

void Pong::handleKeyUp(unsigned char key, int x, int y) {
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

void Pong::moveRackets() {
    racketLeft.move(gameCtrlKeys[0], gameCtrlKeys[1], height);
    racketRight.move(gameCtrlKeys[2], gameCtrlKeys[3], height);
}

void Pong::moveBall() {
    ball.move(
        scoreLeft,
        scoreRight,
        racketLeft.getX(),
        racketLeft.getY(),
        racketRight.getX(),
        racketRight.getY(),
        Racket::getWidth(),
        Racket::getHeight(),
        width,
        height
    );
}

void Pong::resetGame() {
    scoreLeft = 0;
    scoreRight = 0;

    // Reset the position of the rackets
    racketLeft.setX(10.0f);
    racketLeft.setY(height / 2.0f - Racket::getHeight() / 2.0f);
    racketRight.setX(width - Racket::getWidth() - 10.0f);
    racketRight.setY(height / 2.0f - Racket::getHeight() / 2.0f);

    // Reset the position and direction of the ball
    ball.setPosX(width / 2.0f);
    ball.setPosY(height / 2.0f);
    ball.setDirX(-1.0f);
    ball.setDirY(0);

    isPaused = false;

    glutPostRedisplay();
}

void Pong::toggleXMode() {
    resetGame();
    xModeEnabled = !xModeEnabled;
}

bool Pong::gameEnded() {
    return ((scoreLeft >= 2) || (scoreRight >= 2));
}

std::string Pong::gameWonMessage() {
    std::string message;
    if (scoreLeft > scoreRight) {
        message = "Left Player Won";
    } else if (scoreLeft < scoreRight) {
        message = "Right Player Won";
    }

    return message;
}

std::string Pong::scoreToString() {
    return std::to_string(scoreLeft) + " : " + std::to_string(scoreRight);
}
