#include "Game.h"


int main(void)
{
    game simpleGame("Trial", 1200, 1200);
    simpleGame.gameInitialization();
    simpleGame.gameLoop();
}