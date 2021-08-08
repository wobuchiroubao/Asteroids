//#include <utility>
//#include <tuple>
#include <cmath>

#include "engine.h"
#include "game.h"

using namespace std;

const int SPACESHIP_WIDTH = 30;
const int SPACESHIP_HEIGHT = 30;
const Vector<int> MODEL_VERTICES[3] = {{20, 0}, {-10, 10}, {-10,-10}};
const size_t ASTEROIDS_NUM = 1;

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

class SpaceShip final {
public:
  SpaceShip(const Vector<int> *model_vertices);
  SpaceShip(
    Vector<int> position, Angle<float> angle, int width, int height,
    Vector<int> velocity, const Vector<int> *model_vertices
  );
  void Init(
    Vector<int> position, Angle<float> angle, int width, int height,
    Vector<int> velocity
  );
  void Update(float dt);
  void Render() const;

  Vector<int> model_vertices_[3];
  Vector<int> transformed_vertices_[3];
  Vector<int> position_;
  Angle<float> angle_;
  int width_;
  int height_;
  Vector<int> velocity_;

private:
  void UpdateVertices();
};

SpaceShip::SpaceShip(const Vector<int> *model_vertices)
: model_vertices_({model_vertices[0], model_vertices[1], model_vertices[2]}) {}

SpaceShip::SpaceShip(
  Vector<int> position, Angle<float> angle, int width, int height,
  Vector<int> velocity, const Vector<int> *model_vertices
)
: model_vertices_({model_vertices[0], model_vertices[1], model_vertices[2]})
, position_(position)
, angle_(angle)
, width_(width)
, height_(height)
, velocity_(velocity) {
  UpdateVertices();
}

void SpaceShip::Init(
  Vector<int> position, Angle<float> angle, int width, int height,
  Vector<int> velocity
) {
  SpaceShip ss(position, angle, width, height, velocity, model_vertices_);
  *this = ss;
}

void SpaceShip::Update(float dt) {
  position_ += dt * velocity_;
  WrapCoord(position_.x_, position_.y_);
  UpdateVertices();
}

void SpaceShip::Render() const {
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  for (int x = position_.x_, x_end = position_.x_ + width_; x < x_end; ++x) {
    for (int y = position_.y_, y_end = position_.y_ + height_; y < y_end; ++y) {
      WrapRenderPoint(renderer, x, y);
    }
  }
}

void SpaceShip::UpdateVertices() {
  for (size_t i = 0; i < 3; ++i) {
    transformed_vertices_[i] = model_vertices_[i].Rotate(angle_);
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

SpaceShip spaceship(MODEL_VERTICES);
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
      spaceship.angle_ -= M_PI / 6;
      break;

    case K_RIGHT:
      spaceship.angle_ += M_PI / 6;
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
