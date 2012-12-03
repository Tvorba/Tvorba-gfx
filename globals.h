#include <SDL2/SDL.h>

#ifndef GLOBALS_H
#define GLOBALS_H

SDL_Window *pWindow;
SDL_GLContext glContext;
SDL_Thread *eventThread, *logicThread;

#endif // GLOBALS_H
