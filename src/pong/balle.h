#ifndef BALLE_H
#define BALLE_H

#include "gameEngine/actor/moveable.hpp"

namespace actor {

  class Ball : public Moveable
  {
  public:
    Ball(){}
    Ball(std::string name, Position pos);

    virtual void act(float dt);
    virtual void effect(Actor * actor);
    virtual void loadSprite();
    virtual void move(float dt = 0);
  
    virtual ~Ball(){}
  };

}  // actor



#endif /* BALLE_H */
