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

#include "context.h"

namespace tvorba {

  Context::Context() :
    is_quiting(false),
    return_value(EXIT_FAILURE)
  {
  }

  Context::~Context()
  {
    this->is_quiting=true;
    std::thread *current_thread, **local_copy;
    for(local_copy=threads;(local_copy-threads) > num_threads; local_copy++)
      {
        current_thread=*local_copy;
        if(current_thread)
          {
            current_thread->join();
            delete current_thread;
          }
      }
    free((void*)threads);
  }

  void Context::init_graphics(char *title)
  {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window  = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1440, 900,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                           /*#ifndef DEBUG
                               | SDL_WINDOW_FULLSCREEN
                           #endif*/
                               );

    if(window == nullptr)
      {
        fprintf(stderr, "ERROR: Could not create window: %s\n", SDL_GetError());
        is_quiting = true;
        return_value = EXIT_FAILURE;
      }

    gl_context = SDL_GL_CreateContext(window);
    if(gl_context == nullptr)
      {
        fprintf(stderr, "ERROR: Could not create OpenGL context: %s\n", SDL_GetError());
        is_quiting = true;
        return_value = EXIT_FAILURE;
      }

    if (glewInit() != GLEW_OK)
      {
        fprintf(stderr, "ERROR: Failed to initialize GLEW\n");
        is_quiting = true;
        return_value = EXIT_FAILURE;
      }

    SDL_ShowCursor(SDL_DISABLE);
    if(SDL_ShowCursor(SDL_QUERY) != SDL_DISABLE)
      {
        fputs("WARN: Unable to hide cursor.", stderr);
      }
  }
}
