#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

#include "gameEngine/actor/building/building.h"

#include "gameEngine/actor/mobs/mob.h"

#include "gameEngine/actor/character/controlable.h"


void move(actor::Actor * c, float dt)
{
  // Cast the actor in Controlable to call the move function of controlable
  dynamic_cast<actor::Controlable *>(c)->move(dt);
}

void generate(Stage * stage)
{
  int w,h;

  getDimensionWindow(&w, &h);
  
  stage->player = &(stage->create<actor::Controlable>("Jack", Position(w/2, h/2, 100,100))); // Create an actor controlable
  stage->player->addActStatement(move); // Add a statement to the actor
  stage->create<actor::Mob>("cow", 10, Position(0,0,233,170)); // Create a mob
  stage->create<actor::Building>("bloc", Position(200, 200, 100, 100)); // Create o bloc
}


int main(int argc, char *argv[])
{
  Game game(800,800);
  
  game.run(generate);
  
  return EXIT_SUCCESS;
}
