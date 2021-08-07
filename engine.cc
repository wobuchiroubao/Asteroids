#include <SDL2/SDL.h>
#include <iostream>

#include "engine.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
  SDL_Window* window = NULL;
  SDL_Surface* screen_surface = NULL; // rendering surface
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  }
  window = SDL_CreateWindow(
    "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
  );
  if(window == NULL) {
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
  }
  screen_surface = SDL_GetWindowSurface(window);
  SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000); // wait two seconds

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
