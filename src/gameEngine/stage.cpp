#include <algorithm>
#include <fstream>
#include <iostream>

#include "stage.h"

#include "actor/character/controlable.h"

#include "actor/objectives/objective.h"

#include "actor/mobs/mob.h"

void Stage::create(size_t hash)
{  
  if(hash == typeid(actor::Controlable).hash_code())
    player = &create<actor::Controlable>();
  else if(hash == typeid(actor::FoodObjective).hash_code())
    create<actor::FoodObjective>();
  else
    std::cout << "AH" << "\n";  
}

Stage::Stage(int width, int height) : _vp{width, height}
{
  for(int i=0;i < NB_OBJ_EVENT;i++)
    _objectiveEvent[i] = 0;
}

void Stage::remove(ActorPtr & actor) 
{ 
  Actors::iterator it = std::find_if(_actors.begin(), _actors.end(), 
				     [&actor] (ActorPtr const & it) { return it.get() == actor.get(); });
  _actors.erase(it);
}

void Stage::act(float dt)
{
  ActorPtr * toDelete(nullptr);
  
  for (auto & a : _actors)
    {
      if(toDelete)
	{
	  remove(*toDelete);
	  toDelete = nullptr;
	}
      else
	{
	  a->act(dt);

	  if(a->isDead())
	    toDelete = &a;
	}
    }

  if(toDelete)
    {
      remove(*toDelete);
      toDelete = nullptr;
    }
}

void Stage::save()
{
  std::ofstream out(FILE_SAVE);
  int           length = std::count_if(_actors.begin(), _actors.end(), [](const ActorPtr & actor) { return actor->getPosition().use; } ); /* Number of actor */

  if(out.is_open())
    {
      out.write((char *)&length, sizeof(int));
  
      for(auto & a : _actors)
	{
	  if(a->getPosition().use)
	    {
	      size_t hash = typeid(*a).hash_code(); /* Hashcode of an object to identify the type of the actor */
	      //std::cout << hash << "\n";
	      out.write((char *)&hash, sizeof(size_t));
	      a->save(out);
	      a->saveAnnexe(out);
	    }
	}

      out.close();
    }
}

void Stage::load()
{
  std::ifstream in(FILE_SAVE);
  int           length;
  size_t        hash;

  if(in.is_open())
    {
      in.read((char *) &length, sizeof(int));

      for(int i=0; i < length; ++i)
	{
	  in.read((char *) &hash, sizeof(size_t));
	  
	  create(hash);

	  _actors.back().get()->load(in);
	  _actors.back().get()->loadSprite();
	  _actors.back().get()->loadAnnexe(in);
	}
    }

  in.close();
}

void Stage::generate()
{
  gen(this);
}

int Stage::getObjEvent(int event)
{
  int ret = _objectiveEvent[event];

  _objectiveEvent[event] = 0;

  return ret;
}
