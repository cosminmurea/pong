# C++ / GLUT Pong

Simple Pong game developed using C++ and GLUT / OpenGL.

# 1. Installation

The game has been developed and tested on Ubuntu 20.04 LTS.<br>

- <span style="font-size: 1.5rem">Requirements</span>
    - Git
    - G++
    - Make
    - Freeglut
- <span style="font-size: 1.5rem">Steps</span>
    1. Move to the directory where you want to clone this repository.
    2. Clone the project using :
        ```
        git clone https://github.com/cosminmurea/pong.git
        ```
    3. Install the needed dependencies using :
        ```
        sudo apt-get install freeglut3 freeglut3-dev
        sudo apt-get install binutils-gold
        ```
    4. Move to the newly created '/pong' directory and run the 'make' command.
    5. Enjoy the game.

# 2. Controls

W - Move left racket up<br>
S - Move left racket down<br>
I - Move right racket up<br>
K - Move right racket down<br>
R - Resume game<br>
N - New game<br>
X - Enable X-Mode<br>
F - Toggle full-screen mode<br>
Esc - Quit game

# 3. Screenshots

<img src="images/glutGame.png" alt="GLUT Pong Game" width="900" height="400"/>
<img src="images/glutMenu.png" alt="GLUT Pong Menu" width="900" height="400"/>
<img src="images/glutGameWon.png" alt="GLUT Pong Game Won" width="900" height="400"/>
