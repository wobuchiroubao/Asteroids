#include <iostream>
#include <chrono>
#include <tuple>

#include "engine.h"

using namespace std;

Engine::Engine(int screen_width, int screen_height)
: screen_width_(screen_width)
, screen_height_(screen_height)
, window_(NULL)
, renderer_(NULL)
, texture_(NULL)
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
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_TARGETTEXTURE);
  texture_ = SDL_CreateTexture(
    renderer, TEXTURE_FORMAT, SDL_TEXTUREACCESS_TARGET,
    SCREEN_WIDTH, SCREEN_HEIGHT
  );
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

pair<SDL_Renderer *, SDL_Texture *> Engine::GetRenderer() {
  SDL_SetRenderTarget(renderer_, texture_);
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  return make_pair(renderer_, texture_);
}

void Engine::Render() {
  RenderAll();
  SDL_SetRenderTarget(renderer_, NULL); // set window as render target
  SDL_RenderCopy(renderer_, texture_, NULL, NULL); // stamp target onto window*/
  SDL_RenderPresent(renderer_); // update window
}

void Engine::Finalize() {
  SDL_DestroyTexture(texture_);
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

SDL_Renderer *renderer;
SDL_Texture *texture;

int main() {
  Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (engine.Initialize()) {
    cout << "Initialization failed." << endl;
    return -1;
  }

  InitializeAll();

  auto prev_time = chrono::steady_clock::now();
  chrono::time_point<std::chrono::steady_clock> cur_time;
  bool quit = false;
  while (!quit) {
    quit = engine.PollEvents();
    cur_time = chrono::steady_clock::now();
    engine.Update(chrono::duration<float>(cur_time - prev_time).count());
    prev_time = cur_time;
    tie(renderer, texture) = engine.GetRenderer();
    engine.Render();
    SDL_Delay(20); // wait 0.02 seconds
  }

  engine.Finalize();

  return 0;
}
