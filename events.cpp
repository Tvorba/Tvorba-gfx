/* events.cpp
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

#include "events.h"
#include "entity.h"
#include "event.h"

namespace tvorba {
  int event_loop(void *context)
  {
    Context *main_context = (Context*) context;
    SDL_Event *event = new SDL_Event;

    while(!main_context->is_quiting)
      {
        if(SDL_WaitEvent(event) == 0)
          {
            fprintf(stderr, "ERROR waiting for events: %s", SDL_GetError());
            //return EXIT_FAILURE;
          }

        /*#ifdef DEBUG
      fprintf(stderr, "DEBUG: EventType %i\n", event->type);
#endif*/

        if(event->type == SDL_QUIT)
          {
            main_context->return_value = EXIT_SUCCESS;
            main_context->is_quiting = true;
          }
        main_context->entities.all(
              [&event] (Entity *self){ self->event( new Event(event) ); });

      }

    return EXIT_SUCCESS;
  }
}
