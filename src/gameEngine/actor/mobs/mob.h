#ifndef MOB_H
#define MOB_H

#include "../actor.h"

#define INIT_SPEED 1.f
#define INIT_WAIT 1000

enum MobState{COOL, RUNNING, ATTACKING, FOLLOWING};

namespace actor {

  class Mob : public Actor
  {
  private:
    float _time;
    int   _distance;
    int   _waitingTime;
  protected:
    int   _state;
    float _speed;
  public:
    Mob(){}
    Mob(std::string name, float life, Position pos);

    virtual void act(float dt);
    virtual void effect(){};
    virtual void loadSprite() { Actor::loadSprite("../sprites/mobs/"); }
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
  };


}  // actor

#endif /* MOB_H */
