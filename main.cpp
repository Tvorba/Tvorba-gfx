/* main.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <thread>

#include <SDL2/SDL.h>

#include <config.h>
#include <context.h>
#include <events.h>
#include <render.h>

using namespace tvorba;

int main(int argc, char **argv)
{
  fprintf(stderr, "Tvorba-" VERSION " on %s\n", SDL_GetPlatform());

  Context *main_context = new Context();
  main_context->init_graphics("Tvorba-" VERSION);

  SDL_GL_MakeCurrent(main_context->window, nullptr); // Free OpenGL acces from this thread

  main_context->num_threads = std::thread::hardware_concurrency();
  main_context->num_threads = (main_context->num_threads >= 4) ? main_context->num_threads : 4;

  main_context->threads = (std::thread**) malloc(main_context->num_threads * sizeof(void*));
  main_context->threads[0] = new std::thread(render_loop, main_context);
  main_context->threads[1] = new std::thread(event_loop, main_context);

  while(!main_context->is_quiting)
    {
      std::this_thread::yield();
    }

  delete main_context;
  return main_context->return_value;

}
