#include <iostream>

#include "engine.h"

using namespace std;

Engine::Engine(int screen_width, int screen_height)
: screen_width_(screen_width)
, screen_height_(screen_height)
, window_(NULL)
, screen_surface_(NULL)
{}

int Engine::Initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << endl;
    return -1;
  }
  window_ = SDL_CreateWindow(
    "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    screen_width_, screen_height_, SDL_WINDOW_SHOWN
  );
  if(window_ == NULL) {
    cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
    return -1;
  }
  screen_surface_ = SDL_GetWindowSurface(window_);
  return 0;
}

void Engine::Render() {
  SDL_FillRect(
    screen_surface_, NULL, SDL_MapRGB(screen_surface_->format, 0x00, 0x00, 0x00)
  );
  SDL_Rect rect;

  rect.x = 10;
  rect.y = 0;
  rect.w = 60;
  rect.h = 30;
  FillRect(rect, SDL_MapRGB(screen_surface_->format, 0x00, 0x00, 0xFF));
  SDL_UpdateWindowSurface(window_);
  SDL_Delay(2000); // wait two seconds
}

void Engine::FillRect(const SDL_Rect& rect, Uint32 color) {
  SDL_FillRect(screen_surface_, &rect, color);
}

void Engine::Finalize() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

int main() {
  Engine engine;
  if (engine.Initialize()) {
    cout << "Initialization failed." << endl;
    return -1;
  }
  engine.Render();

  engine.Finalize();

  return 0;
}
