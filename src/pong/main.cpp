#include <Box2D/Box2D.h>

#include "gameEngine/game.h"
#include "gameEngine/actor/controlable/controlable.h"
#include "gameEngine/ihm/color.h"
#include "gameEngine/ihm/keyboard.h"
#include "gameEngine/actor/static.h"

void move1(actor::Actor * a, float dt)
{
  dynamic_cast<actor::Controlable *>(a)->moveX(); // Cast in Controlable to call moveX(). moveX() move the actor on the X axis
}

void move2(actor::Actor * a, float dt)
{
  dynamic_cast<actor::Controlable *>(a)->moveX();
}

void collisionBall(actor::Actor * ball, actor::Actor * a)
{
  b2Vec2 vec = ball->body()->GetLinearVelocity();
  
  if(a->getName() == "Wall") vec.x *= -1;
  else if(a->getName() == "Death") a->stage()->endStage();
  else {
    b2Vec2 posBall = ball->body()->GetPosition();
    b2Vec2 posActor = a->body()->GetPosition();

    vec.x = 5*((posBall.x - posActor.x)/ball->getPosition().w/2);
    vec.y *= -1;
  }

  ball->body()->SetLinearVelocity(vec);
}

void generate(Stage * s)
{
  actor::Actor * a;
  int w, h;
  
  getDimensionWindow(&w, &h); // Get the width and the height of the window
  
  a = &s->create<actor::Controlable>("Player1", 1, Position(w/2.f,12, 100, 10)); // Create an actor controlable
  a->loadSprite(Color::white); // Load a white rectangle
  a->addActStatement(move1); // Add a new statement to the actor
  dynamic_cast<actor::Controlable *>(a)->setSpeed(10.f);
  
  a = &s->create<actor::Controlable>("Player2", 1, Position(w/2.f,h - 20,100,10)); // Create player 2
  a->loadSprite(Color::white);
  a->addActStatement(move2);
  dynamic_cast<actor::Controlable *>(a)->setSpeed(10.f);
  
  a = &s->create<actor::Moveable>("Ball", 1,Position(w/2,h/2,10,10));
  a->addCollisionOnStatement(collisionBall);
  a->loadSprite(Color::white);
  a->body()->SetLinearVelocity(b2Vec2(0,-10));
  
  s->create<actor::Static>("Wall", Position(-10,0,10,h));
  s->create<actor::Static>("Wall", Position(w,0,10,h)); // Create a second wall
  s->create<actor::Static>("Death", Position(0,-10,w,10));
  s->create<actor::Static>("Death", Position(0,h,w,10));
  
  s->addMusic("../sound/music.wav"); // Load the level music
  s->playMusic(0); // Play the music
}

int main()
{
  Game pong(800,800,"pong"); // Create the game

  pong.run(generate); //run the game with the generation
  
  return 0;
}
