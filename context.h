/* context.h
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

#include <glm/glm.hpp>

#include <thread>

#include <entity.h>

#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

namespace tvorba {
  using namespace glm;
  using namespace std;

  class Context
  {
  public:
    Context();
    ~Context();

    unsigned num_threads;
    thread **threads;

    SDL_Window *window;
    SDL_GLContext gl_context;

    mat4 view, projection;
    Entity *entities;

    bool is_quiting;
    int return_value;
  };
}

#endif // RENDERCONTEXT_H
