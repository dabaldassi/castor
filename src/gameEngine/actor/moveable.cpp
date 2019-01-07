#include <algorithm>
#include <Box2D/Box2D.h>

#include "moveable.hpp"
#include "../stage.h"

using actor::Moveable;

Moveable::Moveable(const std::string & name, float life, const Position & p):Actor(name, life, p)
{
  b2BodyDef bodyDef;
  Position pos = p / Viewport::METER_TO_PIXEL;
  
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(pos.x + pos.w / 2, pos.y + pos.h/2);
  _body = Stage::world().CreateBody(&bodyDef);

  
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(pos.w/2.f, pos.h/2.f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 0.5f;
  fixtureDef.friction = 0.8f;
  
  _body->CreateFixture(&fixtureDef);
  _body->SetUserData((void *)this);
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

void Moveable::loadSprite(const char *path)
{
  Actor::loadSprite(path);
}

Moveable::~Moveable()
{}
