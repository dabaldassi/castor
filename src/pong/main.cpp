
#include "gameEngine/game.h"
#include "gameEngine/actor/character/controlable.h"
#include "gameEngine/ihm/color.h"
#include "gameEngine/ihm/keyboard.h"
#include "gameEngine/actor/static.h"
#include "balle.h"

void move1(actor::Actor * a, float dt)
{
  dynamic_cast<actor::Controlable *>(a)->moveX(); // Cast in Controlable to call moveX(). moveX() move the actor on the X axis
  dynamic_cast<actor::Controlable *>(a)->searchCollision(); // Cast in Controlable to call the method searchcollision 
}

void move2(actor::Actor * a, float dt)
{
  dynamic_cast<actor::Controlable *>(a)->moveX();
  dynamic_cast<actor::Controlable *>(a)->searchCollision(); 
}

void generate(Stage * s)
{
  actor::Actor * a;
  int w, h;
  
  getDimensionWindow(&w, &h); // Get the width and the height of the window
  
  a = &s->create<actor::Controlable>("Player1", Position(w/2.f,12, 100, 10)); // Create an actor controlable
  a->loadSprite(Color::white); // Load a white rectangle
  a->addActStatement(move1); // Add a new statement to the actor

  a = &s->create<actor::Controlable>("Player2", Position(w/2.f,h - 2,100,10)); // Create player 2
  a->loadSprite(Color::white);
  a->addActStatement(move2);

  s->create<actor::Static>("Wall", Position(-10,h,10,h)); // Create a Wall to avoid exiting the screen
  s->create<actor::Static>("Wall", Position(w,h,10,h)); // Create a second wall
  
  s->create<actor::Ball>("Ball", Position(w/2,h/2,10,10));
}

int main()
{
  Game pong(800,800,"pong"); // Create the game

  pong.run(generate); //run the game with the generation
  
  return 0;
}