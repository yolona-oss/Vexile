#include "Vexile/Core/Math/Angle.hpp"

#include <cmath>

namespace Vexile {

Angle::Angle(float rad) : _rad(rad) {}

Angle::Angle(const Angle &other) { _rad = other._rad; }

Angle::Angle(const Angle &&other) { _rad = other._rad; }

Angle &Angle::operator=(const Angle &other) {
  _rad = other._rad;
  return *this;
}

Angle &Angle::operator=(const Angle &&other) {
  _rad = other._rad;
  return *this;
}

Angle Angle::fromRadians(float rad) { return rad; }
Angle Angle::fromDegrees(float deg) { return deg * M_PI / 180; }

float Angle::radians() const { return _rad; }
float Angle::degrees() const { return _rad * 180 / M_PI; }

Angle::operator float() { return _rad; }
Angle::operator int() { return static_cast<int>(_rad); }

Angle operator"" _deg(long double angle) { return Angle::fromDegrees(angle); }
Angle operator"" _deg(unsigned long long int angle) { return Angle::fromDegrees(angle); }
Angle operator"" _rad(long double angle) { return Angle::fromRadians(angle); }
Angle operator"" _rad(unsigned long long int angle) { return Angle::fromRadians(angle); }

bool operator==(const Angle &left, const Angle &right) { return left.radians() == right.radians(); }
bool operator!=(const Angle &left, const Angle &right) { return left.radians() != right.radians(); }
bool operator<(const Angle &left, const Angle &right) { return left.radians() < right.radians(); }
bool operator>(const Angle &left, const Angle &right) { return left.radians() > right.radians(); }
bool operator<=(const Angle &left, const Angle &right) { return left.radians() <= right.radians(); }
bool operator>=(const Angle &left, const Angle &right) { return left.radians() >= right.radians(); }

Angle operator+(const Angle &left, const Angle &right) { return left + right; }
Angle operator-(const Angle &left, const Angle &right) { return left - right; }
Angle operator*(const Angle &left, const Angle &right) { return left * right; }
Angle operator/(const Angle &left, const Angle &right) { return left / right; }
Angle operator%(const Angle &left, const Angle &right) { return left % right; }
Angle &operator+=(Angle &left, Angle right) { return left = left + right; }
Angle &operator-=(Angle &left, Angle right) { return left = left - right; }
Angle &operator*=(Angle &left, Angle right) { return left = left * right; }
Angle &operator/=(Angle &left, Angle right) { return left = left / right; }
Angle &operator%=(Angle &left, Angle right) { return left = left % right; }

} // namespace Vexile
