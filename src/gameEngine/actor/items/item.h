/**
 *\file item.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef ITEM_H
#define ITEM_H

#include "../actor.h"

namespace actor {

  /**
   *\class Item
   *\brief Object that can be used by the player
   */
  
  class Item : public Actor
  {
  protected:
    bool  _onTheGround; /* If the item is on the ground, it can be picked */
    float _weight;
  public:
    Item(){}
    Item(std::string name, float weight)
      : Actor(name, 1), _weight(weight) {}
    Item(std::string name, Position pos, float weight);

    void setOnGround() { _onTheGround = true; }
    bool isOnTheGround() const { return _onTheGround; }
    float getWeight() const { return _weight; }
    
    virtual void effect();
    virtual void update();
    virtual void loadSprite() { Actor::loadSprite("../sprites/items/"); }
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
  };


}  // actor

#endif /* ITEM_H */
