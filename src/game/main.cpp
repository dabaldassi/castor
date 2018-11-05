#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

#include "gameEngine/actor/building/building.h"

#include "gameEngine/actor/mobs/mob.h"

#include "gameEngine/actor/controlable/controlable.h"


void move(actor::Actor * c, float dt)
{
  // Cast the actor in Controlable to call the move function of controlable
  dynamic_cast<actor::Controlable *>(c)->move(dt);
  dynamic_cast<actor::Controlable *>(c)->moveCamera();
  dynamic_cast<actor::Controlable *>(c)->searchCollision();
}

void effect(actor::Actor * c, actor::Actor * c2)
{
  std::cout << c->getName() << ": salut" << "\n";

  c->playSound(0);
  
}

void effectCow(actor::Actor *c, actor::Actor * c2)
{
  std::cout << c->getName() << ": meuh" << "\n";
}

void generate(Stage * stage)
{
  int w,h;

  getDimensionWindow(&w, &h);
  
  stage->player = &(stage->create<actor::Controlable>("Jack", 1, Position(w/2, h/2, 100,100))); // Create an actor controlable
  stage->player->addActStatement(move); // Add a statement to the actor
  stage->player->addEffectStatement(effect);
  stage->player->addSound("../sound/hit.wav");
  
  stage->create<actor::Mob>("cow", 10, Position(0,0,233,170)).addEffectStatement(effectCow); // Create a mob
  stage->create<actor::Building>("bloc", Position(200, 200, 100, 100)); // Create o bloc
}


int main(int argc, char *argv[])
{
  Game game(800,800, "Super Game");
  
  game.run(generate);
  
  return EXIT_SUCCESS;
}
