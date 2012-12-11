#include <events.h>

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

      switch(event->type)
        {
        case SDL_QUIT:
#ifdef DEBUG
          fputs("DEBUG: Qutting\n", stderr);
#endif
          main_context->is_quiting = true;
          main_context->return_value = EXIT_SUCCESS;
          break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
          SDL_KeyboardEvent key = event->key;
#ifdef DEBUG
          fprintf(stderr, "DEBUG: Key%s %c\n", (event->type == SDL_KEYDOWN) ? "Down" : "Up", key.keysym.sym);
#endif
          break;
        }
    }

  return EXIT_SUCCESS;
}

