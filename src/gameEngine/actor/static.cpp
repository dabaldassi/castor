#include <Box2D/Box2D.h>

#include "../stage.cpp"
#include "static.h"

using actor::Static;

Static::Static(const std::string & name, const Position & pos):Actor(name, 1, pos)
{
  b2BodyDef bodyDef;
  bodyDef.position.Set(pos.x, pos.y);

  _body = Stage::world().CreateBody(&bodyDef);

  b2PolygonShape box;
  box.SetAsBox(pos.w / 2.f, pos.h / 2.f);

  _body->CreateFixture(&box, 0.0f);
  
  loadSprite();
}

void Static::loadSprite()
{
  int color[4];
  
  getColorWindow(color);

  Actor::loadSprite(color);
}
