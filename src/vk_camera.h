#pragma once

#include <SDL2/SDL.h>

class Camera {
public:
  // camera position
  float x = 0.f, y = -5.0f, z = -1.5f;

  void update(const SDL_Event *e) {
    if (e->type == SDL_MOUSEWHEEL) {
      if (e->wheel.y > 0) // scroll up
      {
        movespeed += 0.2;
      } else if (e->wheel.y < 0) // scroll down
      {
        movespeed -= 0.2;
      }
    } else if (e->type == SDL_KEYDOWN) {
      switch (e->key.keysym.sym) {
      case SDLK_z:
        moveforwards = true;
        break;
      case SDLK_q:
        moveleft = true;
        break;
      case SDLK_s:
        movebackwards = true;
        break;
      case SDLK_d:
        moveright = true;
        break;
      case SDLK_a:
        movedown = true;
        break;
      case SDLK_e:
        moveup = true;
        break;
      }
    } else if (e->type == SDL_KEYUP) {
      switch (e->key.keysym.sym) {
      case SDLK_z:
        moveforwards = false;
        break;
      case SDLK_q:
        moveleft = false;
        break;
      case SDLK_s:
        movebackwards = false;
        break;
      case SDLK_d:
        moveright = false;
        break;
      case SDLK_a:
        movedown = false;
        break;
      case SDLK_e:
        moveup = false;
        break;
      }
    }
  }

  void move() {
    if (moveright)
      x -= movespeed;
    if (moveleft)
      x += movespeed;
    if (movebackwards)
      z -= movespeed;
    if (moveforwards)
      z += movespeed;
    if (moveup)
      y += movespeed;
    if (movedown)
      y -= movespeed;
  }

  void resetPos() { x = 0.f, y = -0.15f, z = -1.5f; }

private:
  bool moveforwards = false;
  bool movebackwards = false;
  bool moveright = false;
  bool moveleft = false;
  bool moveup = false;
  bool movedown = false;
  float movespeed = 0.1;
};
