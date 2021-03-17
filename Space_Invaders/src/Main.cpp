#include <iostream>

#include "GameLogic.h"

int main()
{
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