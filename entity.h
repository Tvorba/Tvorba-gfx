#include <SDL2/SDL.h>

#ifndef ENTITY_H
#define ENTITY_H

namespace tvorba
{

  class Entity
  {
  public:
    Entity();

    Entity *previous, *next;
    bool pop(void);
    bool push(Entity *entity);
  };

}
#endif // ENTITY_H
