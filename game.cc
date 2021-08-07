#include "engine.h"
#include "game.h"

template <typename T>
class Vector2 final {
public:
  Vector2() = default;
  Vector2(T x, T y);
  Vector2& operator+=(const Vector2& rhs);
  Vector2& operator-=(const Vector2& rhs);
  T x_, y_;
};

template <typename T>
Vector2<T>::Vector2(T x, T y)
: x_(x)
, y_(y)
{}

template <typename T>
Vector2<T> operator-(const Vector2<T>& v) {
  return Vector2<T>(-v.x_, -v.y_);
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs) {
  Vector2<T> tmp = -rhs;
  x_ += tmp.x_;
  y_ += tmp.y_;
  return *this;
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
  return Vector2<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
  return lhs + (-rhs);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& lhs, float rhs) {
  return Vector2<T>(lhs.x_ * rhs, lhs.y_ * rhs);
}

template <typename T>
Vector2<T> operator*(float lhs, const Vector2<T>& rhs) {
  return rhs * lhs;
}

const int SPACESHIP_WIDTH = 20;
const int SPACESHIP_HEIGHT = 20;

class SpaceShip final {
public:
  SpaceShip(Vector2<int> position, int width, int height, Vector2<int> velocity);
  void Update(float dt);
  void Render() const;
  operator SDL_Rect() const;

  Vector2<int> position_;
  int width_;
  int height_;
  Vector2<int> velocity_;
};

SpaceShip::SpaceShip(
  Vector2<int> position, int width, int height, Vector2<int> velocity
)
: position_(position)
, width_(width)
, height_(height)
, velocity_(velocity)
{}

void SpaceShip::Update(float dt) {
  position_ += dt * velocity_;
}

void SpaceShip::Render() const {
  SDL_Rect rect = *this;
  SDL_FillRect(buffer, &rect, SDL_MapRGB(buffer->format, 0xFF, 0xFF, 0xFF));
}

SpaceShip::operator SDL_Rect() const {
  return {position_.x_, position_.y_, width_, height_};
}

SpaceShip spaceship(
  {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
  SPACESHIP_WIDTH, SPACESHIP_HEIGHT,
  {0, 0}
);

void Engine::Update(float dt) {
  keyword key = GetKey();
  switch (key) {
    case NONE:
      break;

    case K_UP:
      break;

    case K_DOWN:
      break;

    case K_LEFT:
      break;

    case K_RIGHT:
      break;
  }
}

void Engine::Render() {
  /*SDL_Rect rect;

  rect.x = 10;
  rect.y = 0;
  rect.w = 60;
  rect.h = 30;
  FillRect(rect, SDL_MapRGB(screen_surface_->format, 0x00, 0x00, 0xFF));*/
  spaceship.Render();
  SDL_BlitSurface(buffer, NULL, screen_surface_, NULL);
  SDL_UpdateWindowSurface(window_);
}
