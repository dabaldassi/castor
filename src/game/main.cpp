#include "gameEngine/ihm/keyboard.h"

#include "gameEngine/game.h"

#include "gameEngine/actor/static.h"

#include "gameEngine/actor/mobs/mob.h"

#include "gameEngine/actor/controlable/controlable.h"

#include "gameEngine/ihm/color.h"


class DataPlayer : public actor::Data
{
public:
  int a;
};

void move(actor::Actor * c, float dt)
{
  // Cast the actor in Controlable to call the move function of controlable
  dynamic_cast<actor::Controlable *>(c)->move(dt);
  dynamic_cast<actor::Controlable *>(c)->moveCamera();
  dynamic_cast<actor::Controlable *>(c)->searchCollision();
}

void soundCollision(actor::Actor * c, actor::Actor * c2)
{
  c->playSound(0);
}

void effect(actor::Actor * c, actor::Actor * c2)
{
  std::cout << c->getName() << ": salut" << "\n";
  
  std::cout << c->getData<DataPlayer *>()->a << "\n";
}

void effectCow(actor::Actor *c, actor::Actor * c2)
{
  std::cout << c->getName() << ": meuh" << "\n";
}

void click(actor::Actor * a, int b)
{
  std::cout << "click" << "\n";
}

void generate(Stage * stage)
{
  DataPlayer * data = new DataPlayer;
  int w,h;
  actor::Actor * a;
  

  data->a = 8;

  getDimensionWindow(&w, &h);
  
  stage->player = &(stage->create<actor::Controlable>("Jack", 1, Position(w/2, h/2, 100,100))); // Create an actor controlable
  stage->player->addOnClickEvent(click);
  stage->player->addActStatement(move); // Add a statement to the actor
  stage->player->addCollisionOnStatement(effect);
  stage->player->addCollisionOnStatement(soundCollision);
  stage->player->addSound("../sound/hit.wav");
  stage->player->setData(data);
  
  stage->create<actor::Mob>("cow", 10, Position(0,0,233,170)).addCollisionOnStatement(effectCow); // Create a mob

  
  a = &stage->create<actor::Static>("bloc", Position(200, 200, 100, 100)); // Create a bloc
  a->loadSprite(Color::green);

  a = &stage->create<actor::Static>("ground", Position(0,0,2*w,10));
  a->loadSprite(Color::green);
  //printf("%f\n", a->getPosition().h);
  
  stage->world().SetGravity(b2Vec2(0,-10));
  
  //a = &stage->create<actor::Static>("bloc", Position(0, 0, 100, 100)); // Create a bloc
  //a->loadSprite(Color::green);
}


int main(int argc, char *argv[])
{
  Game game(800,800, "Super Game");
  
  game.run(generate);
  
  return EXIT_SUCCESS;
}
