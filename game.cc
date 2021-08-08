#include "engine.h"
#include "game.h"

const size_t ASTEROIDS_NUM = 3;

template <typename T, typename U>
class FreedomDegrees final {
public:
  FreedomDegrees() = default;
  FreedomDegrees(T x, T y, U alpha);
  FreedomDegrees& operator+=(const FreedomDegrees& rhs);
  FreedomDegrees& operator-=(const FreedomDegrees& rhs);
  T x_, y_;
  U alpha_;

private:
  void LoopBack();
};

template <typename T, typename U>
FreedomDegrees<T, U>::FreedomDegrees(T x, T y, U alpha)
: x_(x)
, y_(y)
, alpha_(alpha)
{}

template <typename T, typename U>
void FreedomDegrees<T, U>::LoopBack() {
  alpha_ %= 360;
  if (alpha_ < 0) {
    alpha_ += 360;
  }
}

template <typename T, typename U>
FreedomDegrees<T, U> operator-(const FreedomDegrees<T, U>& fd) {
  return FreedomDegrees<T, U>(-fd.x_, -fd.y_, -fd.alpha_);
}

template <typename T, typename U>
FreedomDegrees<T, U>& FreedomDegrees<T, U>::operator+=(
  const FreedomDegrees& rhs
) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  alpha_ += rhs.alpha_;
  LoopBack();
  return *this;
}

template <typename T, typename U>
FreedomDegrees<T, U>& FreedomDegrees<T, U>::operator-=(
  const FreedomDegrees<T, U>& rhs
) {
  FreedomDegrees<T, U> tmp = -rhs;
  x_ += tmp.x_;
  y_ += tmp.y_;
  alpha_ += tmp.alpha_;
  LoopBack();
  return *this;
}

template <typename T, typename U>
FreedomDegrees<T, U> operator+(
  const FreedomDegrees<T, U>& lhs, const FreedomDegrees<T, U>& rhs
) {
  return FreedomDegrees<T, U>(
    lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.alpha_ + rhs.alpha_
  );
}

template <typename T, typename U>
FreedomDegrees<T, U> operator-(
  const FreedomDegrees<T, U>& lhs, const FreedomDegrees<T, U>& rhs
) {
  return lhs + (-rhs);
}

template <typename T, typename U>
FreedomDegrees<T, U> operator*(const FreedomDegrees<T, U>& lhs, float rhs) {
  return FreedomDegrees<T, U>(lhs.x_ * rhs, lhs.y_ * rhs, lhs.alpha_ * rhs);
}

template <typename T, typename U>
FreedomDegrees<T, U> operator*(float lhs, const FreedomDegrees<T, U>& rhs) {
  return rhs * lhs;
}

const int SPACESHIP_WIDTH = 20;
const int SPACESHIP_HEIGHT = 20;

class SpaceShip final {
public:
  SpaceShip() = default;
  SpaceShip(
    FreedomDegrees<int, int> position, int width, int height,
    FreedomDegrees<int, int> velocity
  );
  void Init(
    FreedomDegrees<int, int> position, int width, int height,
    FreedomDegrees<int, int> velocity
  );
  void Update(float dt);
  void Render() const;
  operator SDL_Rect() const;

  FreedomDegrees<int, int> position_;
  int width_;
  int height_;
  FreedomDegrees<int, int> velocity_;
};

SpaceShip::SpaceShip(
  FreedomDegrees<int, int> position, int width, int height,
  FreedomDegrees<int, int> velocity
)
: position_(position)
, width_(width)
, height_(height)
, velocity_(velocity)
{}

void SpaceShip::Init(
  FreedomDegrees<int, int> position, int width, int height,
  FreedomDegrees<int, int> velocity
) {
  SpaceShip ss(position, width, height, velocity);
  *this = ss;
}

void SpaceShip::Update(float dt) {
  position_ += dt * velocity_;
}

void SpaceShip::Render() const {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 100, 100, 400, 200);
}

SpaceShip::operator SDL_Rect() const {
  return {position_.x_, position_.y_, width_, height_};
}

class Asteroid final {
public:
  Asteroid() = default;
  Asteroid(
    FreedomDegrees<int, int> position, int radius,
    FreedomDegrees<int, int> velocity
  );
  void Init(
    FreedomDegrees<int, int> position, int radius,
    FreedomDegrees<int, int> velocity
  );
  void Update(float dt);
  void Render() const;

  FreedomDegrees<int, int> position_;
  int radius_;
  FreedomDegrees<int, int> velocity_;
};

Asteroid::Asteroid(
  FreedomDegrees<int, int> position, int radius,
  FreedomDegrees<int, int> velocity
)
: position_(position)
, radius_(radius)
, velocity_(velocity)
{}

void Asteroid::Init(
  FreedomDegrees<int, int> position, int radius,
    FreedomDegrees<int, int> velocity
) {
  Asteroid ast(position, radius, velocity);
  *this = ast;
}

void Asteroid::Update(float dt) {
  position_ += dt * velocity_;
}

void Asteroid::Render() const {

}

SpaceShip spaceship(
  {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -90},
  SPACESHIP_WIDTH, SPACESHIP_HEIGHT,
  {0, 0, 0}
);
Asteroid asteroids[ASTEROIDS_NUM];
//for (auto& asteroid : asteroids) {
//  asteroid.Init(

//  );
//}

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

void RenderAll() {
  spaceship.Render();
  for (const auto& asteroid : asteroids) {
    asteroid.Render();
  }
}
