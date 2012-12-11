#include <glm/glm.hpp>

#include <entity.h>

#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

namespace tvorba {
  using namespace glm;

  class Context
  {
  public:
    Context();
    ~Context();

    SDL_Thread *event_thread, *logic_thread, *render_thread;

    SDL_Window *window;
    SDL_GLContext gl_context;

    mat4 view, projection;
    Entity *entities;

    bool is_quiting;
    int return_value;
  };
}

#endif // RENDERCONTEXT_H
