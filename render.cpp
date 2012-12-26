/* render.cpp
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

#include <render.h>

using namespace tvorba;

int tvorba::render_loop(Context *main_context)
{
  SDL_GL_MakeCurrent(main_context->window, main_context->gl_context);
  //SDL_GL_SwapWindow(pWindow);

  while(!main_context->is_quiting)
    {
      glClearColor(0.0, 0.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for(Entity *current = &(main_context->entities); current; current = current->next)
        {
          current->render(main_context);
        }

      fputs(SDL_GetError(), stderr);

      SDL_GL_SwapWindow(main_context->window);
    }
}
