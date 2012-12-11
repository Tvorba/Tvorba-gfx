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
    // SDL_WaitThread(this->logic_thread, NULL); We have not enabled logic yet
    SDL_WaitThread(this->render_thread, NULL);
    SDL_WaitThread(this->event_thread, NULL);
  }
}
