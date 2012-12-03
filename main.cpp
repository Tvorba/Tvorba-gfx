#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_opengl.h>

#include <globals.h>
#include <events.h>

#define WIDTH 640
#define HEIGHT 480

void quit(int ret);

void checkError(int line = -1)
{
  fputs(SDL_GetError(), stderr);
}

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  fprintf(stderr, "Tvorba 0.1.0-alpha on %s\n", SDL_GetPlatform());

  /*  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); */

  pWindow  = SDL_CreateWindow("Tvorba 0.1.0-alpha",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                            #ifndef DEBUG
                              | SDL_WINDOW_FULLSCREEN
                            #endif
                              );

  if(pWindow == NULL)
    {
      fprintf(stderr, "ERROR: Could not create window: %s\n", SDL_GetError());
      quit(EXIT_FAILURE);
    }

  glContext = SDL_GL_CreateContext(pWindow);
  if(glContext == NULL)
    {
      fprintf(stderr, "ERROR: Could not create opengl context: %s\n", SDL_GetError());
      quit(EXIT_FAILURE);
    }

  checkError(__LINE__);

#ifndef DEBUG
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(pWindow);
#else
  glClearColor(0.0, 1.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(pWindow);
#endif

  SDL_ShowCursor(SDL_DISABLE);
  if(SDL_ShowCursor(SDL_QUERY) != SDL_DISABLE)
    {
      fputs("WARN: Unable to hide cursor.", stderr);
    }

  eventThread = SDL_CreateThread(eventLoop, "Events", pWindow);
//  logicThread = SDL_CreateThread(logicLoop, eventThread);
  int ret;
  SDL_WaitThread(eventThread, &ret);
  quit(ret);
}

void quit(int ret)
{
  SDL_DestroyWindow(pWindow);
  exit(ret);
}
