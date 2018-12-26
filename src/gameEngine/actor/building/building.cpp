#include "building.h"
#include "../../stage.h"
#include "../controlable/controlable.h"

using actor::Building;

Building::Building(std::string name, Position pos):Static(name, pos)
{
  loadSprite();
}

void Building::effect()
{
}

void Building::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Actor::save(out);
      _trigger.save(out);
    }
}

void Building::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Actor::load(in);
      _trigger.load(in);
    }
}
