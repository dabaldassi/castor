#include "moveable.hpp"
#include "../stage.h"

using actor::Moveable;

void Moveable::update(Viewport const & vp)
{
  Actor::update(vp);
}

void Moveable::save(std::ofstream &out)
{
  Actor::save(out);

  if(out.is_open())
    {
      out.write((char *)&_speed, sizeof(float));
    }
}


void Moveable::load(std::ifstream &in)
{
  Actor::load(in);

  if(in.is_open()) {
    in.read((char *)&_speed, sizeof(float));

  }
}

void Moveable::searchCollision()
{
  for(auto & a: _stage->actors())
    {
      if(a.get() == this)
	continue;
      else
	if(a.get()->getHitbox().use && a.get()->getHitbox().collide(_position, _orientation, _speed))
	  {
	    a.get()->effect();
	  }
    }
}

void Moveable::loadSprite(const char *path)
{
  Actor::loadSprite(path);
}

Moveable::~Moveable()
{}
