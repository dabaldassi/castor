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
  if(_distance == 0 && _time < _waitingTime)
    _time += dt;

  if(_time >= _waitingTime)
    {
      _orientation = std::rand()%1;
      _time = 0;
      _distance = std::rand()%170 + 30;
      _waitingTime = 1000 + (std::rand()%5000);
    }

  if(_distance > 0)
    {
      _position.x += _speed * ((_orientation == W || _orientation == NW || _orientation == SW) - (_orientation == E || _orientation == NE || _orientation == SE));
      _position.y += _speed * ((_orientation == N || _orientation == NW || _orientation == NE) - (_orientation == S || _orientation == SE || _orientation == SW));
      --_distance;
    }
}

void Mob::act(float dt)
{
  move(dt);
  
  searchCollision();
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
