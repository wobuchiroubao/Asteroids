#pragma once

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
class Vector {
public:
  Vector();
  Vector(T x, T y);
  template <typename U>
  Vector<T> Rotate(const Angle<U>& angle) const;
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
template <typename U>
Vector<T> Vector<T>::Rotate(const Angle<U>& angle) const {
  Vector<T> v;
  v.x_ = cos(angle) * x_ - sin(angle) * y_;
  v.y_ = sin(angle) * x_ + cos(angle) * y_;

  return v;
}

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
