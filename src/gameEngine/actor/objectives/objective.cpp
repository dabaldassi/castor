#include <string>

#include "objective.h"

#include "../../stage.h"

#include "../../ihm/color.h"

using namespace actor;

Objective::Objective(std::string name, int limit, int id):Actor(name,1), _limit(limit), _current(0), _id(id)
{
  _position = Position(0,id*50, 300, 100);
  
  loadSprite();
 
}

void Objective::update(Viewport const & vp)
{
  if(_elem)
    {
      setTextElement(_elem, (_name + " " +  std::to_string(_current) + " / " + std::to_string(_limit)).c_str());
    }
}

void Objective::loadSprite()
{
  _elem = createText(_position.x, _position.y, _position.w, _position.h, 60, OBJ_FONT,(_name + " " +  std::to_string(_current) + " / " + std::to_string(_limit)).c_str(), Color::white, SANDAL2_BLENDED, 0, 2);
}

void Objective::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Actor::save(out);

      out.write((char *)&_current, sizeof(int));
      out.write((char *)&_limit, sizeof(int));
      out.write((char *)&_id, sizeof(int));
    }
}

void Objective::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Actor::load(in);

      in.read((char *)&_current, sizeof(int));
      in.read((char *)&_limit, sizeof(int));
      in.read((char *)&_id, sizeof(int));
    }
}

FoodObjective::FoodObjective(std::string name, int limit, int id, int event[]):Objective(name, limit, id)
{
  event[FOOD] = 0;
}

void FoodObjective::act(float dt)
{
  if(isComplete())
    {
      kill();
    }
  else
    _current += _stage->getObjEvent(FOOD);
}
