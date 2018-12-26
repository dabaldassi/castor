#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener
{
  void BeginContact(b2Contact * contact);
  void EndContact(b2Contact * contact);
};


#endif /* CONTACTLISTENER_H */
