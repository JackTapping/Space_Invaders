#include <iostream>
#include "GameLogic.h"

int main()
{
    //seedig random for the Sensor Of set veriable in the GameLogic class
    srand(time(NULL));

    //Class that controls the game
    GameLogic game;

    //Main Loop
    while (game.isWindowOpen())
    {
        //render screen
        game.Update();

        //draw here 
        game.Render();
        
    }

    return 0;
}