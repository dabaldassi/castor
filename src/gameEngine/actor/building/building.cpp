#include "building.h"
#include "../../stage.h"
#include "../controlable/controlable.h"

using actor::Building;

Building::Building(std::string name, Position pos):Static(name, pos)
{
  loadSprite();
  
  //_trigger = Position(pos.x + (555 * pos.w/597),pos.y - (291 * pos.h / 434), 50, 50); /* Set the trigger */

  /* Drawing the hitbox */
  
  /*_hitbox.addLine(LineBox(Position(pos.x + (215 * pos.w/597),pos.y - (160 * pos.h / 434)), Position(pos.x + (215 * pos.w/597), pos.y - (260 * pos.h / 434))));
  _hitbox.addLine(LineBox(Position(pos.x + (215 * pos.w/597),pos.y - (160 * pos.h / 434)), Position(pos.x + (498 * pos.w/597), pos.y - (2 * pos.h / 434))));
  _hitbox.addLine(LineBox(Position(pos.x + (498 * pos.w/597),pos.y - (2 * pos.h / 434)), Position(pos.x + (570 * pos.w/597), pos.y - (106 * pos.h / 434))));
  _hitbox.addLine(LineBox(Position(pos.x + (232 * pos.w/597),pos.y - (360 * pos.h / 434)), Position(pos.x + (376 * pos.w/597), pos.y - (429 * pos.h / 434))));
  _hitbox.addLine(LineBox(Position(pos.x + (376 * pos.w/597), pos.y - (429 * pos.h / 434)), Position(pos.x + (546 * pos.w/597),pos.y - (343 * pos.h / 434))));
  _hitbox.addLine(LineBox(Position(pos.x + (570 * pos.w/597),pos.y - (231 * pos.h / 434)), Position(pos.x + (570 * pos.w/597), pos.y - (106 * pos.h / 434)))); */

}

void Building::effect()
{
  if(_stage->player->getHitbox().collide(_trigger))
    {
      std::cout << "*triggered*" << "\n";
    }
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
