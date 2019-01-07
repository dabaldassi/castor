#include "weapon.h"

using actor::Weapon;

void Weapon::effect(actor::Actor *actor)
{
  if(_effectfct2.size() != 0) Actor::effect(actor);
  else actor->takeDamage(_damage);
}

void Weapon::effect()
{
  if(_effectfct.size() != 0) Actor::effect();
}

void Weapon::set(float damage, float distance)
{
  _damage = damage;
  _distance = distance;
}
