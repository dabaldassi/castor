/**
 *\file mob.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef MOB_H
#define MOB_H

#include "../moveable.hpp"

#define INIT_SPEED 1.f
#define INIT_WAIT 1000

enum MobState{COOL, RUNNING, ATTACKING, FOLLOWING};

namespace actor {

  class Mob : public Moveable
  {
  private:
    float _time;
    int   _distance;
    int   _waitingTime;
  protected:
    int   _state;
  public:
    Mob(){}
    Mob(std::string name, float life, Position pos);

    virtual void act(float dt);
    virtual void loadSprite() { Moveable::loadSprite("../sprites/mobs/"); }
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
    virtual void move(float dt = 0);
  };


}  // actor

#endif /* MOB_H */
