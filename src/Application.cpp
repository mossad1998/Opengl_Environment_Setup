#include "Game.h"
#include <GL/glut.h>


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    game simpleGame("Trial", 1200, 1200);
    simpleGame.gameInitialization();
    simpleGame.gameLoop();
}