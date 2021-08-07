#pragma once

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
extern SDL_Surface *buffer;

enum keyword {
  NONE,
  K_UP,
  K_DOWN,
  K_LEFT,
  K_RIGHT,
};

class Engine final {
public:
  Engine(int screen_width=640, int screen_height=480);
  int Initialize();
  bool PollEvents();
  keyword GetKey();
  void Update(float dt);
  void Render();
  void Finalize();

private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Surface *screen_surface_;
  keyword key_;
};
