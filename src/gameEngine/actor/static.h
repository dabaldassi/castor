#ifndef STATIC_H
#define STATIC_H

#include "actor.h"

namespace actor {
  
  class Static : public Actor
  {
  public:
    Static(){}
    Static(std::string name, Position pos)
      :Actor(name, 1, pos) { loadSprite(); }
    
    virtual void loadSprite();
  
    virtual ~Static(){}
  };

}  // actor

#endif /* STATIC_H */
