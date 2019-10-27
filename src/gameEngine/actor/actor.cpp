#include "SANDAL2.h"
#include "actor.h"
#include "../stage.h"
#include <iostream>
#include <Box2D/Box2D.h>

using actor::Actor;
using actor::Data;

void Actor::update(Viewport const & vp)
{
  float const mToP = Viewport::METER_TO_PIXEL;

  if (_elem)
    {
      b2Vec2 pos = _body->GetPosition();
      
      replaceElement(_elem, mToP * (pos.x - vp.x - _position.w/2), mToP * (vp.height - _position.h /2 -pos.y + vp.y));
      setDimensionElement(_elem, mToP * _position.w, mToP * _position.h);
      setAngleElement(_elem, -_body->GetAngle()*180/M_PI);
    }
}

void Actor::act(float dt)
{
  for(auto a: _actfct) a(this, dt);
}

void Actor::effect()
{
  for(auto a: _effectfct) a(this);
}


void Actor::effect(Actor * actor)
{
  for(auto a: _effectfct2)
    a(this, actor);
}

void click(Element * e, int b)
{
  Data * data;
  getDataElement(e, (void **)&data);
  
  if(data->getActor()->onClick)
    data->getActor()->onClick(data->getActor(), b);
}

Actor::Actor()
{
  _elem = NULL;
  _body = NULL;
  _life = 0;
  _position = Position(0,0,0,0);
  _position.use = false;
  onClick = NULL;
}

Actor::Actor(const std::string & name, float life):_elem(nullptr), _life(life), _name(name)
{
  onClick = NULL;
}

Actor::Actor(const std::string & name, float life, const Position & pos) :_position(pos/Viewport::METER_TO_PIXEL),_elem(nullptr), _life(life), _name(name)
{
  _body = NULL;
  onClick = NULL;
}

Actor::~Actor()
{
  if(_elem)
    {
      delElement(_elem);
      _elem = NULL;
    }

  if(_body) {
    b2JointEdge * j = _body->GetJointList();
    _body->SetUserData(NULL);
    
    while(j) {
      
      _stage->world().DestroyJoint(j->joint);
      j = j->next;
    }
    
    _stage->world().DestroyBody(_body);
  }

  std::for_each(_sounds.begin(), _sounds.end(), [](auto it) { Mix_FreeChunk(it.second); });
  
}

void Actor::save(std::ofstream &out)
{
  if(out.is_open())
    {
      _position.save(out);
      out.write((char *)&_life, sizeof(float));

      int length = _name.length() + 1;

      out.write((char *)&length, sizeof(int));
      out.write((char *)_name.c_str(), sizeof(char)*length);
      out.write((char *)&_orientation, sizeof(int));
    }
}

void Actor::load(std::ifstream &in)
{
  if(in.is_open())
    {
      _position.load(in);
      in.read((char *)&_life, sizeof(float));

      int length;

      in.read((char *)&length, sizeof(int));

      char name[100];

      in.read((char *)name, sizeof(char)*length);
      _name = name;

      in.read((char *)&_orientation, sizeof(int));

    }
}

void Actor::loadSprite(const char path[])
{
  int green[] = {0,255,0,0};

  if(_elem) setImageElement(_elem, path);
  else
    _elem = createImage(_position.x, _position.y, _position.w, _position.h, path, 0, 0);
  
  if(_elem == NULL) // Default
    _elem = createBlock(_position.x, _position.y, _position.w, _position.h, green, 0, 0);
}

void Actor::loadSprite(int color[4])
{
  if(_elem) setColorElement(_elem, color);
  else
    _elem = createBlock(_position.x, _position.y, _position.w, _position.h, color, 0, 0);
}

void Actor::addSound(const std::string & path)
{
  Mix_Chunk * sound;

  sound = Mix_LoadWAV(path.c_str());

  if(sound) {
    _sounds.emplace(std::make_pair(path, sound));
  }
  else
    std::cerr << "Failed to open : " << path << "\n";
}

void Actor::playSound(const std::string & name)
{
  int ch = 0;

  auto search = _sounds.find(name);
  
  if(search != _sounds.end()) {

    while(Mix_Playing(ch)) ch++;
    
    Mix_PlayChannel(ch,search->second, 0);
  }
}

void Actor::setData(Data * data)
{
  Data * tmp;
  
  getDataElement(_elem, (void **)&tmp);

  if(tmp)
    Data::free(tmp);
    
  data->setActor(this);
  
  setDataElement(_elem, (void *)data);
  setFreeDataElement(_elem, Data::free);
}

void Data::setActor(Actor * actor)
{
  _actor = actor;
}

void Actor::addOnClickEvent(std::function<void(Actor *, int)> fct)
{
  onClick = fct;
  setOnClickElement(_elem, click);
  addClickableElement(_elem, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
}

void Actor::collisionOn(actor::Actor *actor)
{
  for(auto f:_collisionOn) f(this,actor);
}

void Actor::collisionOff(actor::Actor *actor)
{
  for(auto f:_collisionOff) f(this,actor);
}

b2Vec2 operator*(const b2Vec2 & v, float coeff)
{
  return b2Vec2(v.x * coeff ,v.y * coeff);
}
