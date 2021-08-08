//#include <utility>
//#include <tuple>
#include <cmath>

#include "engine.h"
#include "game.h"

using namespace std;

const size_t ASTEROIDS_NUM = 1;

template <typename T>
class Vector {
public:
  Vector();
  Vector(T x, T y);
  Vector& operator+=(const Vector& rhs);
  Vector& operator-=(const Vector& rhs);

  T x_, y_;
};

template <typename T>
Vector<T>::Vector()
: x_(0)
, y_(0) {}

template <typename T>
Vector<T>::Vector(T x, T y)
: x_(x)
, y_(y) {}

template <typename T>
Vector<T> operator-(const Vector<T>& v) {
  return Vector<T>(-v.x_, -v.y_);
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs) {
  Vector<T> tmp = -rhs;
  x_ += tmp.x_;
  y_ += tmp.y_;
  return *this;
}

template <typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  return Vector<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

template <typename T>
Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs) {
  return lhs + (-rhs);
}

template <typename T>
Vector<T> operator*(const Vector<T>& lhs, float rhs) {
  return Vector<T>(lhs.x_ * rhs, lhs.y_ * rhs);
}

template <typename T>
Vector<T> operator*(float lhs, const Vector<T>& rhs) {
  return rhs * lhs;
}

template <typename T>
class Angle final {
public:
  Angle() = default;
  Angle(T angle);
  Angle& operator+=(const Angle& rhs);
  Angle& operator-=(const Angle& rhs);
  operator T() const;

  T angle_;

private:
  void LoopBack();
};

template <typename T>
Angle<T>::Angle(T angle)
: angle_(angle) {
  LoopBack();
}

template <typename T>
Angle<T>::operator T() const {
  return angle_;
}

template <typename T>
void Angle<T>::LoopBack() {
  fmod(angle_, 2 * M_PI);
  if (angle_ < 0) {
    angle_ += 2 * M_PI;
  }
}

template <typename T>
Angle<T> operator-(const Angle<T>& angle) {
  return Angle<T>(-angle.angle_);
}

template <typename T>
Angle<T>& Angle<T>::operator+=(
  const Angle& rhs
) {
  angle_ += rhs.angle_;
  LoopBack();
  return *this;
}

template <typename T>
Angle<T>& Angle<T>::operator-=(
  const Angle<T>& rhs
) {
  Angle<T> tmp = -rhs;
  angle_ += tmp.angle_;
  LoopBack();
  return *this;
}

template <typename T>
Angle<T> operator+(const Angle<T>& lhs, const Angle<T>& rhs) {
  return Angle<T>(lhs.angle_ + rhs.angle_);
}

template <typename T>
Angle<T> operator-(const Angle<T>& lhs, const Angle<T>& rhs) {
  return lhs + (-rhs);
}

template <typename T>
Angle<T> operator*(const Angle<T>& lhs, T rhs) {
  return Angle<T>(lhs.angle_ * rhs);
}

template <typename T>
Angle<T> operator*(T lhs, const Angle<T>& rhs) {
  return rhs * lhs;
}

template <typename T>
void WrapCoord(T& x, T& y) {
  if (x < 0) {
    x += SCREEN_WIDTH;
  } else if (x > SCREEN_WIDTH) {
    x -= SCREEN_WIDTH;
  }
  if (y < 0) {
    y += SCREEN_HEIGHT;
  } else if (y > SCREEN_HEIGHT) {
    y -= SCREEN_HEIGHT;
  }
}

void WrapRenderPoint(SDL_Renderer *renderer, int x, int y) {
  WrapCoord(x, y);
  SDL_RenderDrawPoint(renderer, x, y);
}

const int SPACESHIP_WIDTH = 20;
const int SPACESHIP_HEIGHT = 30;

class SpaceShip final {
public:
  SpaceShip() = default;
  SpaceShip(
    Vector<int> position, Angle<float> angle,
    int width, int height, Vector<int> velocity
  );
  void Init(
    Vector<int> position, Angle<float> angle,
    int width, int height, Vector<int> velocity
  );
  void Update(float dt);
  void Render() const;

  Vector<int> position_;
  Angle<float> angle_;
  int width_;
  int height_;
  Vector<int> velocity_;
};

SpaceShip::SpaceShip(
  Vector<int> position, Angle<float> angle,
  int width, int height, Vector<int> velocity
)
: position_(position)
, angle_(angle)
, width_(width)
, height_(height)
, velocity_(velocity)
{}

void SpaceShip::Init(
  Vector<int> position, Angle<float> angle,
  int width, int height, Vector<int> velocity
) {
  SpaceShip ss(position, angle, width, height, velocity);
  *this = ss;
}

void SpaceShip::Update(float dt) {
  position_ += dt * velocity_;
  WrapCoord(position_.x_, position_.y_);
}

void SpaceShip::Render() const {
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  for (int x = position_.x_, x_end = position_.x_ + width_; x < x_end; ++x) {
    for (int y = position_.y_, y_end = position_.y_ + height_; y < y_end; ++y) {
      WrapRenderPoint(renderer, x, y);
    }
  }
}

class Asteroid final {
public:
  Asteroid() = default;
  Asteroid(Vector<int> position, int radius, Vector<int> velocity);
  void Init(Vector<int> position, int radius, Vector<int> velocity);
  void Update(float dt);
  void Render() const;

  Vector<int> position_;
  int radius_;
  Vector<int> velocity_;
};

Asteroid::Asteroid(Vector<int> position, int radius, Vector<int> velocity)
: position_(position)
, radius_(radius)
, velocity_(velocity)
{}

void Asteroid::Init(Vector<int> position, int radius, Vector<int> velocity) {
  Asteroid ast(position, radius, velocity);
  *this = ast;
}

//#include <iostream>

void Asteroid::Update(float dt) {
  position_ += dt * velocity_;
  //std::cout << dt << std::endl;
  WrapCoord(position_.x_, position_.y_);
}

void Asteroid::Render() const {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  for (int x = position_.x_, x_end = position_.x_ + radius_; x < x_end; ++x) {
    for (int y = position_.y_, y_end = position_.y_ + radius_; y < y_end; ++y) {
      WrapRenderPoint(renderer, x, y);
    }
  }
}

SpaceShip spaceship;
Asteroid asteroids[ASTEROIDS_NUM];

void InitializeAll() {
  spaceship.Init(
    {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, -M_PI / 2,
    SPACESHIP_WIDTH, SPACESHIP_HEIGHT, {0, 0}

  );
  for (auto& asteroid : asteroids) {
    asteroid.Init({100, 100}, 60, {100, 60});
  }
}

void Engine::Update(float dt) {
  keyword key = GetKey();
  switch (key) {
    case NONE:
      break;

    case K_UP:
      spaceship.velocity_ += {
        50 * cos(spaceship.angle_), 50 * sin(spaceship.angle_)
      };
      break;

    case K_DOWN:
      break;

    case K_LEFT:
      break;

    case K_RIGHT:
      break;
  }
  spaceship.Update(dt);
  for (auto& asteroid : asteroids) {
    asteroid.Update(dt);
  }
}

void RenderAll() {
  spaceship.Render();
  for (const auto& asteroid : asteroids) {
    asteroid.Render();
  }
}
