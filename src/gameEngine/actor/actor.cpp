#include "../../SANDAL2/SANDAL2.h"
#include "actor.h"

using actor::Actor;

void Actor::update(Viewport const & vp)
{
  float const mToP = Viewport::METER_TO_PIXEL;

  if (_elem)
    {
      Position pos = _position;

      replaceElement(_elem, mToP * (pos.x - vp.x), mToP * (vp.height - pos.y + vp.y));
      setDimensionElement(_elem, mToP * pos.w, mToP * pos.h);
    }
}

void Actor::act(float dt)
{
  for(auto a: _actfct)
    a(this, dt);
}

void Actor::effect()
{
  for(auto a: _effectfct)
    a(this);
}


void Actor::effect(Actor * actor)
{
  for(auto a: _effectfct2)
    a(this, actor);
}

Actor::Actor()
{
  _elem = NULL;
  _life = 0;
  _position = Position(0,0,0,0);
  _position.use = false;
}

Actor::~Actor()
{
  if(_elem)
    {
      delElement(_elem);
      _elem = NULL;
    }

  for (unsigned int i = 0; i < _sounds.size(); i++) {
    Mix_FreeMusic(_sounds[i]);
  }
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
      _hitbox.save(out);
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

      _hitbox.load(in);
    }
}

void Actor::loadSprite(const char path[])
{
  int green[] = {0,255,0,0};

  if(_elem) delElement(_elem);
  
  _elem = createImage(_position.x, _position.y, _position.w, _position.h, (path + _name + ".png").c_str(), 0, 0);
  
  if(_elem == NULL) // Default
    _elem = createBlock(_position.x, _position.y, _position.w, _position.h, green, 0, 0);
}

void Actor::loadSprite(int color[4])
{
  if(_elem) delElement(_elem);

  _elem = createBlock(_position.x, _position.y, _position.w, _position.h, color, 0, 0);
}

void Actor::addSound(const char *path)
{
  Mix_Music * sound;

  sound = Mix_LoadMUS(path);

  if(sound) {
    _sounds.push_back(sound);
  }
  else
    std::cerr << "Failed to open : " << path << "\n";
}

void Actor::playSound(unsigned int id)
{
  if(id < _sounds.size()) {
    Mix_PlayMusic(_sounds[id], 0);
  }
}
