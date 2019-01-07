#ifndef STATIC_H
#define STATIC_H

#include "actor.h"

namespace actor {
  
  class Static : public Actor
  {
  public:
    Static(){}
    Static(const std::string & name, const Position & pos);
      
    virtual void loadSprite();
    virtual void addItem(Item * item){}
    virtual void removeItem(Item * item){}
  
    virtual ~Static(){}
  };

}  // actor

#endif /* STATIC_H */
