#include "Vexile/Core/Math/TRS.hpp"

#include <cmath>

namespace Vexile {

TRS::TRS() : Matrixf(4, 4) {}

TRS &TRS::mul(const Matrixf &op) {
  this->_matrix = const_cast<float *>(Matrixf(*this * op).raw());
  return *this;
}

TRS &TRS::translate(const Vector2f &offset) {
  return mul({
      {1.0, 0.0, offset.x, 0.0},
      {0.0, 1.0, offset.y, 0.0},
      {0.0, 0.0, 1.0, 0.0},
      {0.0, 0.0, 0.0, 1.0},
  });
}

TRS &TRS::scale(const Vector2f &factor) {
  return mul({{factor.x, 0.0, 0.0, 0.0},
              {0.0, factor.y, 0.0, 0.0},
              {0.0, 0.0, 1.0, 0.0},
              {0.0, 0.0, 0.0, 1.0}});
}

TRS &TRS::scale(const Vector2f &factor, const Vector2f &center) {
  return mul({{factor.x, 0.0, center.x * (1 - factor.x), 0.0},
              {0.0, factor.y, center.y * (1 - factor.y), 0.0},
              {0.0, 0.0, 1.0, 0.0},
              {0.0, 0.0, 0.0, 1.0}});
}

TRS &TRS::rotate(Angle angle) {
  return mul({{std::cos(angle.radians()), -std::sin(angle.radians()), 0.0, 0.0},
              {std::sin(angle.radians()), std::cos(angle.radians()), 0.0, 0.0},
              {0.0, 0.0, 1.0, 0.0},
              {0.0, 0.0, 0.0, 1.0}});
}

TRS &TRS::rotate(Angle angle, const Vector2f &center) {
  return mul({{std::cos(angle.radians()), -std::sin(angle.radians()), 0.0, 0.0},
              {std::sin(angle.radians()), std::cos(angle.radians()), 0.0, 0.0},
              {0.0, 0.0, 1.0, 0.0},
              {0.0, 0.0, 0.0, 1.0}});
}

} // namespace Vexile
