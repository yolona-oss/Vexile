#pragma once

namespace Vexile {

class Angle {
public:
  Angle(float rad = 0);
  Angle(const Angle &);
  Angle(const Angle &&);

  static Angle fromRadians(float v);
  static Angle fromDegrees(float v);

  float radians() const;
  float degrees() const;

  operator float();
  operator int();
  Angle &operator=(const Angle &);
  Angle &operator=(const Angle &&);

private:
  float _rad{0};
};

float radians();
float degrees();

Angle operator"" _deg(long double angle);
Angle operator"" _deg(unsigned long long int angle);
Angle operator"" _rad(long double angle);
Angle operator"" _rad(unsigned long long int angle);

bool operator==(const Angle &, const Angle &);
bool operator!=(const Angle &, const Angle &);
bool operator<(const Angle &, const Angle &);
bool operator>(const Angle &, const Angle &);
bool operator<=(const Angle &, const Angle &);
bool operator>=(const Angle &, const Angle &);

Angle operator+(const Angle &, const Angle &);
Angle operator-(const Angle &, const Angle &);
Angle operator*(const Angle &, const Angle &);
Angle operator/(const Angle &, const Angle &);
Angle operator%(const Angle &, const Angle &);
Angle &operator+=(Angle &, Angle);
Angle &operator-=(Angle &, Angle);
Angle &operator*=(Angle &, Angle);
Angle &operator/=(Angle &, Angle);
Angle &operator%=(Angle &, Angle);

} // namespace Vexile
