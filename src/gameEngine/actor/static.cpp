#include <Box2D/Box2D.h>

#include "../stage.h"
#include "static.h"

using actor::Static;

Static::Static(const std::string & name, const Position & p):Actor(name, 1, p)
{
  b2BodyDef bodyDef;
  Position pos = p/Viewport::METER_TO_PIXEL;
  bodyDef.position.Set(pos.x + pos.w / 2, pos.y + pos.h/2);

  _body = Stage::world().CreateBody(&bodyDef);

  b2PolygonShape box;
  box.SetAsBox(pos.w / 2.f, pos.h / 2.f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &box;
  fixtureDef.density = 500.f;
  fixtureDef.restitution = 0.f;
  
  _body->CreateFixture(&fixtureDef);
  _body->SetUserData((void *)this);
  
  loadSprite();
}

void Static::loadSprite()
{
  int color[4];
  
  getColorWindow(color);

  Actor::loadSprite(color);
}
