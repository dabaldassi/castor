#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

#include "gameEngine/actor/building/building.h"

#include "gameEngine/actor/mobs/mob.h"

#include "gameEngine/actor/character/controlable.h"

void generate(Stage * stage)
{
  int w,h;

  getDimensionWindow(&w, &h);
  
  stage->player = &(stage->create<actor::Controlable>("Jack", Position(w/2, h/2, 100,100)));
  stage->create<actor::Mob>("cow", 10, Position(0,0,233,170));
  stage->create<actor::Building>("bloc", Position(200, 200, 100, 100));
}

int main(int argc, char *argv[])
{
  Game game(800,800);
  
  game.run(generate);
  
  return EXIT_SUCCESS;
}
