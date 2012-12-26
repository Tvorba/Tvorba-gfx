/* entity.cpp
 * Copyright (C) 2012, Lucas Dohring.
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the Artistic License 2.0 as published by the
 * Perl Foundation. For details, see the full text of the
 * license in the file LICENSE.
 *
 * This program is distributed in the hope that it will be
 * useful, but it is provided “as is” and without any express
 * or implied warranties. For details, see the Artistic License 2.0
 * for more details.
 *
 * You should have received a copy of the Artistic License 2.0
 * along with this code. If not, see <http://www.perlfoundation.org/artistic_license_2_0>
 */

#include "entity.h"
#include <context.h>
#include <event.h>

namespace tvorba
{

  Entity::Entity()
  {
    this->_event  = default_event_handler;
    this->_render = default_null_renderer;
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

  void Entity::all(std::function<void (Entity*)> function)
  {
    function(this);
    if(next != nullptr)
      next->all(function);
  }

  void Entity::all(Entity *entity, std::function<void (Entity*)> function)
  {
    entity->all(function);
  }

  void Entity::on_event(std::function<void (Entity *, Event *)> function)
  {
    _event = std::bind(function, this, std::placeholders::_1);
  }

  void Entity::on_render(std::function<void (Entity *, Context *)> function)
  {
    _render = std::bind(function, this, std::placeholders::_1);
  }

}
