#include <iostream>
#include <stdlib.h>

#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/screen.h"
#include "gameEngine/game.h"

int main(int argc, char *argv[])
{
  Game       game;
  int        black[4] = {255,0,0,0};
  DataWindow dataw = {&game, 1};
 
  if(initAllSANDAL2(IMG_INIT_JPG))
    {
      puts("Failed to init SANDAL2");
      return EXIT_FAILURE;
    }

  createWindow(WIDTH, HEIGHT, NAME, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/ 0, black, GAME);

  if(initIteratorWindow())
    {
      closeAllSANDAL2();
      fprintf(stderr, "Failed to open window \n");
      return EXIT_FAILURE;
    }

  setDataWindow(&dataw);

  Keyboard::init();
  
  game.run();
 
  return EXIT_SUCCESS;
}
