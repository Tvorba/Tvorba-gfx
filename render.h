#define DEBUG

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <context.h>

#ifndef RENDER_H
#define RENDER_H

using namespace glm;
int render_loop(void *context);

#endif // RENDER_H
