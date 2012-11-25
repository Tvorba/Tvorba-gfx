#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_opengl.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pWindow;
  pWindow  = SDL_CreateWindow("Tvorba",
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
    return -1;
  }

  SDL_GLContext glcontext = SDL_GL_CreateContext(pWindow);
  if(glcontext == NULL)
  {
    fprintf(stderr, "ERROR: Could not create opengl context: %s\n", SDL_GetError());
    return -1;
  }



  SDL_DestroyWindow(pWindow);
}
