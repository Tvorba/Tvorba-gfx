/* event.h
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

#ifndef EVENT_H
#define EVENT_H

namespace tvorba {
  typedef enum {
    SDL_EVENT=0,
    NETWORK_EVENT,
    APP_EVENT
  } Event_Type;
  class Event
  {
  public:
    Event();
    Event(SDL_Event *event);
    Event_Type Type(void);

  private:
    void *e;
    Event_Type type;
  };
}

#endif // EVENT_H
