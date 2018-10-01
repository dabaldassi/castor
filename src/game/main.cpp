#include <iostream>
#include <stdlib.h>

#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

#include "gameEngine/actor/building/building.h"

int main(int argc, char *argv[])
{
  Game game(800,800);

  game.stage.create<actor::Building>("bloc", Position(200, 200, 100, 100));
  
  game.run();
 
  return EXIT_SUCCESS;
}
