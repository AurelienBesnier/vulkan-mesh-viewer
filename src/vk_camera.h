#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

class Camera {
public:
  // camera position
  glm::vec3 pos{0.f, -5.0f, -1.5f};
  glm::vec3 front{0.0f, 0.0f, -1.0f};
  glm::vec3 up{0.0f, 1.0f, 0.0f};

  float lastX = 400, lastY = 300;
  const float sensitivity = 0.1f;
  float yaw = -90.0f;
  float pitch = 0.0f;
  bool firstMouse = true;

  void update(const SDL_Event *e) {
    if (e->type == SDL_MOUSEWHEEL) {
      if (e->wheel.y > 0) // scroll up
      {
        movespeed += 0.2;
      } else if (e->wheel.y < 0) // scroll down
      {
        movespeed -= 0.2;
        if (movespeed < 0.1)
          movespeed = 0.1;
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
    } else if (e->type == SDL_MOUSEBUTTONDOWN) {
      if (e->button.button == SDL_BUTTON_LEFT) {
        mousemovement = true;
        SDL_CaptureMouse(SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
      }
    } else if (e->type == SDL_MOUSEBUTTONUP) {
      if (e->button.button == SDL_BUTTON_LEFT) {
        mousemovement = false;
        SDL_CaptureMouse(SDL_FALSE);
        SDL_SetRelativeMouseMode(SDL_FALSE);
        firstMouse = true;
      }
    } else if (e->type == SDL_MOUSEMOTION) {
      if (mousemovement) {
        int xpos, ypos;
        SDL_GetMouseState(&xpos, &ypos);
        if (firstMouse) {
          lastX = xpos;
          lastY = ypos;
          firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
          pitch = 89.0f;
        if (pitch < -89.0f)
          pitch = -89.0f;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
      }
    }
  }

  void move() {
    if (moveright)
      pos += movespeed * glm::normalize(glm::cross(front, up));
    if (moveleft)
      pos -= movespeed * glm::normalize(glm::cross(front, up));
    if (movebackwards)
      pos -= movespeed * front;
    if (moveforwards)
      pos += movespeed * front;
    if (moveup)
      pos.y += movespeed;
    if (movedown)
      pos.y -= movespeed;
  }

  void resetPos() { pos.x = 0.f, pos.y = -0.15f, pos.z = -1.5f; }

private:
  bool mousemovement = false;
  bool moveforwards = false;
  bool movebackwards = false;
  bool moveright = false;
  bool moveleft = false;
  bool moveup = false;
  bool movedown = false;
  float movespeed = 0.1;
};
