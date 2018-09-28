#include <iostream>
#include <stdlib.h>

#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

int main(int argc, char *argv[])
{
  Game       game(800,800);
  
  game.run();
 
  return EXIT_SUCCESS;
}
