#pragma once

#include <SDL2/SDL.h>
#include <utility>

/*SDL_Renderer *renderer = SDL_CreateRenderer(
  window, -1, SDL_RENDERER_TARGETTEXTURE
);
SDL_Texture *texture = SDL_CreateTexture(
  renderer, renderer->texture_formats[0],
  SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT
);
SDL_SetRenderTarget(renderer, texture);
SDL_SetRenderDrawColor(
  renderer, SDL_MapRGB(renderer->texture_formats[0], 0xFF, 0xFF, 0xFF)
);
SDL_RenderClear(renderer);
// render smth
SDL_SetRenderTarget(renderer, NULL); // set window as render target
SDL_RenderCopy(renderer, texture, NULL, NULL); // stamp target onto window*/


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const SDL_PixelFormatEnum TEXTURE_FORMAT = SDL_PIXELFORMAT_RGB888;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

enum keyword {
  NONE,
  K_UP,
  K_DOWN,
  K_LEFT,
  K_RIGHT,
};

void RenderAll();

class Engine final {
public:
  Engine(int screen_width=640, int screen_height=480);
  int Initialize();
  bool PollEvents();
  keyword GetKey();
  void Update(float dt);
  std::pair<SDL_Renderer *, SDL_Texture *> GetRenderer();
  void Render();
  void Finalize();

//private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  SDL_Texture *texture_;
  //SDL_Surface *screen_surface_;
  keyword key_;
};
