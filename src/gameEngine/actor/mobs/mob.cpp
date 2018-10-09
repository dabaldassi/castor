#include <cstdlib>

#include "mob.h"

#include "../../stage.h"

using actor::Mob;

Mob::Mob(std::string name, float life, Position pos):Moveable(name, life, pos)
{
  loadSprite();
  _time = 0;
  _distance = 0;
  _speed = INIT_SPEED;
  _state = COOL;
  _waitingTime = INIT_WAIT;
}

void Mob::move(float dt)
{
  if(_distance == 0 && _time < _waitingTime) // Waiting ...
    _time += dt;

  if(_time >= _waitingTime)
    {
      _orientation = std::rand()%8; // Set the new orientation at random
      _time = 0;
      _distance = std::rand()%170 + 30; // Set the distance that it needs to walk
      _waitingTime = 1000 + (std::rand()%5000); // Set the time it will wait
    }

  if(_distance > 0) // Move the mob
    {
      _position.x += _speed * ((_orientation == W || _orientation == NW || _orientation == SW) - (_orientation == E || _orientation == NE || _orientation == SE));
      _position.y += _speed * ((_orientation == N || _orientation == NW || _orientation == NE) - (_orientation == S || _orientation == SE || _orientation == SW));
      --_distance;
    }
}

void Mob::act(float dt)
{
  if(_actfct.size() != 0) Actor::act(dt); // If there is function to call
  else { // If there is no function this is the default
    move(dt);
  
    searchCollision();
  }
}


void Mob::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Moveable::save(out);

      out.write((char *)&_speed, sizeof(float));
    }
}

void Mob::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Moveable::load(in);

      in.read((char *)&_speed, sizeof(float));
      
      _time = 0;
      _distance = 0;
      _waitingTime = INIT_WAIT;
      _state = COOL;
    }
}
