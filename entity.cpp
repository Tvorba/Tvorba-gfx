#include "entity.h"

namespace tvorba
{

  Entity::Entity()
  {
  }

  bool Entity::pop()
  {
    this->previous->next = this->next;
    return true;
  }

  bool Entity::push(Entity *entity)
  {
    entity->next = this->next;
    this->next = entity;

    entity->next->previous = entity;
    entity->previous = this;

    return true;
  }

}
