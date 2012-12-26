/* entity.h
 * Copyright (C) 2012, Lucas Dohring.
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the Artistic License 2.0 as
 * published by the Perl Foundation. For details, see the
 * full text of the license in the file LICENSE.
 *
 * This program is distributed in the hope that it will be
 * useful, but it is provided “as is” and without any express
 * or implied warranties. For details, see the Artistic License 2.0
 * for more details.
 *
 * You should have received a copy of the Artistic License 2.0
 * along with this code. If not, see <http://www.perlfoundation.org/artistic_license_2_0>
 */

#include <functional>
#include <queue>

#include <SDL2/SDL.h>

#ifndef ENTITY_H
#define ENTITY_H

namespace tvorba
{
  class Context;
  class Event;

  class Entity
  {
  public:
    Entity();

    Entity *previous, *parent, *children, *next;
    bool pop(void);
    bool push(Entity *entity);
    void all(std::function<void(Entity *)> function);
    static void all(Entity *entity, std::function<void(Entity *)> function);

    bool is_render_visible;

    inline void event(Event *e)
    {
      _event(e);
    };

    inline void render(Context *context)
    {
      _render(context);
    };

    void on_event(std::function<void(Entity*, Event*)> function);
    void on_render(std::function<void(Entity*, Context*)> function);

    void *user_data;

    std::queue<Event*> events;

  private:
    std::function<void(Event*)> _event;
    static std::function<void(Event*)> default_event_handler = [this](Event *e){};

    std::function<void(Context*)> _render;
    static std::function<void(Context*)> default_null_renderer = [this](Context *c){};


  };

}
#endif // ENTITY_H
