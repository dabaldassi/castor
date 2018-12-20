#include <algorithm>
#include <Box2D/Box2D.h>

#include "moveable.hpp"
#include "../stage.h"

using actor::Moveable;

Moveable::Moveable(const std::string & name, float life, const Position & p):Actor(name, life, p)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(p.x + p.w / 2, p.y + p.h/2);
  _body = Stage::world().CreateBody(&bodyDef);

  
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(p.w/2.f, p.h/2.f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.f;

  _body->CreateFixture(&fixtureDef);
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
      else {
	auto it = std::find(_collisions.begin(), _collisions.end(), a.get());
	bool collide = a.get()->getHitbox().use && a.get()->getHitbox().collide(_position, _orientation, _speed);
	
	if(collide && it == _collisions.end()) {
	  effect(a.get());
	  _collisions.push_back(a.get());
	}
	else {
	  if(!collide && _collisions.size() > 0 && it != _collisions.end())
	    _collisions.erase(it);
	}

      }
      
    }
}

void Moveable::loadSprite(const char *path)
{
  Actor::loadSprite(path);
}

Moveable::~Moveable()
{}
