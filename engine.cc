#include <iostream>
#include <chrono>

#include "engine.h"

using namespace std;

Engine::Engine(int screen_width, int screen_height)
: screen_width_(screen_width)
, screen_height_(screen_height)
, window_(NULL)
, screen_surface_(NULL)
, key_(NONE)
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

bool Engine::PollEvents() {
  SDL_Event e; // event handler
  if (SDL_PollEvent(&e) == 0) {
    key_ = NONE;
  } else {
    if (e.type == SDL_QUIT) {
      return true;
    } else if (e.type == SDL_KEYDOWN) { // key_ pressed
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          return true;

        case SDLK_UP:
          key_ = K_UP;
          break;

        case SDLK_DOWN:
          key_ = K_DOWN;
          break;

        case SDLK_LEFT:
          key_ = K_LEFT;
          break;

        case SDLK_RIGHT:
          key_ = K_RIGHT;
          break;
      }
    }
  }
  return false;
}

keyword Engine::GetKey() {
  return key_;
}

void Engine::Finalize() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

SDL_Surface *buffer;

int main() {
  buffer = SDL_CreateRGBSurface(
    0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00, 0x00, 0x00, 0x00
  );

  Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (engine.Initialize()) {
    cout << "Initialization failed." << endl;
    return -1;
  }

  auto prev_time = chrono::steady_clock::now();
  chrono::time_point<std::chrono::steady_clock> cur_time;
  bool quit = false;
  while (!quit) {
    quit = engine.PollEvents();
    cur_time = chrono::steady_clock::now();
    engine.Update(chrono::duration<float>(cur_time - prev_time).count());
    prev_time = cur_time;
    engine.Render();
    SDL_Delay(200); // wait 0.2 seconds
  }

  engine.Finalize();

  return 0;
}
