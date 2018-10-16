#include "static.h"

void actor::Static::loadSprite()
{
  int color[4];
  
  getColorWindow(color);

  Actor::loadSprite(color);
}
