#include <Box2D/Box2D.h>

#include "item.h"
#include "../../stage.h"

using actor::Item;

Item::Item(const std::string & name, const Position & p, float weight): Actor(name, 1, p), _weight(weight)
{
  _path = "";
  
  loadSprite();
  
  _onTheGround = true;

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

void Item::update()
{
  if(_onTheGround)
    Actor::update(_stage->viewport());
}

void Item::drop(const b2Vec2 & pos)
{
  _onTheGround = true;

  if(_path != "") loadSprite(_path.c_str());
  else loadSprite(_color);

  b2Fixture * fixture = _body->GetFixtureList();
  
  while(fixture) {
    b2Filter filter = fixture->GetFilterData();
    filter.maskBits = 0xffff;
    fixture->SetFilterData(filter);
    fixture = fixture->GetNext();
  }

  _body->SetTransform(pos, _body->GetAngle());
  
}

Item * Item::pick()
{
  _onTheGround = false;
  _position.use = false;
  delElement(_elem);
  _elem = NULL;

  b2Fixture * fixture = _body->GetFixtureList();
  
  while(fixture) {
    b2Filter filter = fixture->GetFilterData();
    filter.maskBits = 0x0000;
    fixture->SetFilterData(filter);
    fixture = fixture->GetNext();
  }

  return this;
}

void Item::effect()
{

  if(_effectfct.size() == 0) {
  
    /* Pick the item on the floor */
    if(_onTheGround)
      {
	pick();
      }
  }
  else {
    Actor::effect();
  }
}

void Item::save(std::ofstream & out)
{
  if(out.is_open())
    {
      Actor::save(out);
      
      out.write((char *)&_onTheGround, sizeof(bool));
      out.write((char *)&_weight, sizeof(float));
    }
}

void Item::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Actor::load(in);
      in.read((char *)&_onTheGround, sizeof(bool));
      in.read((char *)&_weight, sizeof(float));
    }
}

void Item::loadSprite()
{
  int green[] = {0,255,0,255};
  
  Actor::loadSprite(green);
  
  memcpy(_color, green, sizeof(int)*4);
}

void Item::loadSprite(const char *path)
{
  Actor::loadSprite(path);

  _path = path;
}

void Item::loadSprite(int color[4])
{
  Actor::loadSprite(color);

  memcpy(_color, color, sizeof(int)*4);
}
