#include <SDL2/SDL.h>

class Engine final {
public:
  Engine(int screen_width=640, int screen_height=480);
  int Initialize();
  void Render();
  void FillRect(const SDL_Rect& rect, Uint32 color);
  void Finalize();

private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Surface *screen_surface_;
};
