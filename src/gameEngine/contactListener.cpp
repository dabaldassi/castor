#include <Box2D/Box2D.h>

#include "actor/actor.h"
#include "contactListener.h"

void ContactListener::BeginContact(b2Contact * contact)
{
  void * a1 = contact->GetFixtureA()->GetBody()->GetUserData();
  void * a2 = contact->GetFixtureA()->GetBody()->GetUserData();

  if(a1) {
    static_cast<actor::Actor *>(a1)->collisionOn(static_cast<actor::Actor *>(a2));
  }
}

void ContactListener::EndContact(b2Contact * contact)
{
  void * a1 = contact->GetFixtureA()->GetBody()->GetUserData();
  void * a2 = contact->GetFixtureA()->GetBody()->GetUserData();

  if(a1) {
    static_cast<actor::Actor *>(a1)->collisionOff(static_cast<actor::Actor *>(a2));
  }
}

