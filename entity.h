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
    void render(void);
  };

}
#endif // ENTITY_H
