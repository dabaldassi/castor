#ifndef CASTOR_WEAPON_H
#define CASTOR_WEAPON_H

#include "item.h"

namespace actor {

  class Weapon : public Item
  {
    float _damage;
    float _distance;
    
  public:
    Weapon(){}
    Weapon(const std::string & name, const Position & p, Actor * actor, float weight, float life = 1.f)
      :Item(name,p,actor,weight,life){}
    Weapon(const std::string & name, const Position & p, float weight, float life = 1.f)
      :Item(name, p,weight,life){}

    virtual void set(float damage, float distance);
    virtual float getDamage() const { return _damage; }
    virtual void effect(Actor * actor);
    virtual void effect();
    
    virtual ~Weapon() = default;
  };


}  // actor

#endif /* CASTOR_WEAPON_H */
