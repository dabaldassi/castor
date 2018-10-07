#include "character.h"
#include "../../ihm/color.h"

using actor::Character;

///////////////////////////////////////////////////////////////////////////////
//                                 Character                                  //
///////////////////////////////////////////////////////////////////////////////

Character::Character(std::string name, Position pos):Moveable(name, 100, pos)
{
}

void Character::update(Viewport const & vp)
{
  Moveable::update(vp);
}

void Character::searchCollision()
{
  Moveable::searchCollision();
}

void Character::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Moveable::save(out);
    }
}

void Character::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Moveable::load(in);
    }
}
