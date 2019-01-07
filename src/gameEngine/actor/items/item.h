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
    
    std::string  _path;
    int          _color[4];
    
  public:
    Item(){}
    Item(const std::string & name, float weight)
      : Actor(name, 1), _weight(weight) {}
    Item(const std::string & name, const Position & p, float weight);

    void drop(const b2Vec2 & pos = b2Vec2(0,0));
    bool isOnTheGround() const { return _onTheGround; }
    float getWeight() const { return _weight; }
    
    virtual void effect();
    virtual void update();
    virtual void loadSprite();
    virtual void loadSprite(const char * path);
    virtual void loadSprite(int color[4]);
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual Item * pick();

    virtual ~Item() = default;
  };


}  // actor

#endif /* ITEM_H */
