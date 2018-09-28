#include "character.h"
#include "../../ihm/color.h"

using actor::Character;

///////////////////////////////////////////////////////////////////////////////
//                                 Character                                  //
///////////////////////////////////////////////////////////////////////////////

Character::Character(std::string name, Position pos):Actor(name, 100, pos)
{
}

void Character::effect()
{}

void Character::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Actor::save(out);
    }
}

void Character::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Actor::load(in);
    }
}
