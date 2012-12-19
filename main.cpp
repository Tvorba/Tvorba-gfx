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

#define WIDTH 640
#define HEIGHT 480
using namespace tvorba;

inline void quit(int ret, Context *main_context);

inline void checkError(int line = -1)
{
  const char *err = SDL_GetError();
  if(strlen(err))
    {
      fprintf(stderr, "%s on line %i\n", err, line);
    }
}

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  fprintf(stderr, "Tvorba-" VERSION " on %s\n", SDL_GetPlatform());

  Context *main_context = new Context();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  main_context->window  = SDL_CreateWindow("Tvorba-" VERSION,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           WIDTH, HEIGHT,
                                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                                         #ifndef DEBUG
                                           | SDL_WINDOW_FULLSCREEN
                                         #endif
                                           );

  if(main_context->window == NULL)
    {
      fprintf(stderr, "ERROR: Could not create window: %s\n", SDL_GetError());
      quit(EXIT_FAILURE, main_context);
    }

  main_context->gl_context = SDL_GL_CreateContext(main_context->window);
  if(main_context->gl_context == NULL)
    {
      fprintf(stderr, "ERROR: Could not create OpenGL context: %s\n", SDL_GetError());
      quit(EXIT_FAILURE, main_context);
    }

  if (glewInit() != GLEW_OK)
    {
      fprintf(stderr, "ERROR: Failed to initialize GLEW\n");
      quit(EXIT_FAILURE, main_context);
    }

  checkError(__LINE__);

  SDL_ShowCursor(SDL_DISABLE);
  if(SDL_ShowCursor(SDL_QUERY) != SDL_DISABLE)
    {
      fputs("WARN: Unable to hide cursor.", stderr);
    }

  SDL_GL_MakeCurrent(main_context->window, NULL); // Free OpenGL acces from this thread

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

void quit(int ret, Context *main_context)
{
  main_context->is_quiting = true;
  main_context->return_value = ret;
  delete main_context;
  exit(main_context->return_value);
}
