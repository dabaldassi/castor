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
    Actor     *  _owner;
    bool         _toDisable, _toEnable;
    
  public:
    Item(){}
    Item(const std::string & name, const Position & p, Actor * actor, float weight,float life=1.f);
    Item(const std::string & name, const Position & p, float weight, float life=1.f);

    void drop(const b2Vec2 & pos = b2Vec2(0,0));
    bool isOnTheGround() const { return _onTheGround; }
    float getWeight() const { return _weight; }

    virtual void effect();
    virtual void effect(Actor * actor);
    virtual void update();
    virtual void loadSprite();
    virtual void loadSprite(const char * path);
    virtual void loadSprite(int color[4]);
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual void pick(Actor * actor);
    virtual void addItem(Item * item){}
    virtual void removeItem(Item * item){}
    virtual void act(float dt);

    template <class T=Actor*>
    T getOwner(T actor) { return static_cast<T>(_owner); }

    virtual ~Item() = default;
  };


}  // actor

#endif /* ITEM_H */
