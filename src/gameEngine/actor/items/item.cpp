#include "item.h"
#include "../../stage.h"

using actor::Item;

Item::Item(std::string name, Position pos, float weight): Actor(name, 1, pos), _weight(weight)
{
  loadSprite();
  
  _onTheGround = true;
}

void Item::update()
{
  if(_onTheGround)
    Actor::update(_stage->viewport());
}

void Item::effect()
{
  /* Pick the item on the floor */
  if(_onTheGround)
    {
      _onTheGround = false;
      _hitbox.use = false;
      _position.use = false;
      
      
      delElement(_elem);
      _elem = NULL;
    }
  else {
    std::cout << "yo" << "\n";
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
