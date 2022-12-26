#pragma once

#include "Vexile/Core/Math/Angle.hpp"
#include "Vexile/Core/Math/Matrix.hpp"
#include "Vexile/Core/Math/Vector.hpp"

namespace Vexile {

class TRS : public Matrixf {
public:
  TRS();
  using Matrixf::Matrix;
  virtual ~TRS() {}

  TRS &mul(const Matrixf &);

  TRS &translate(const Vector2f &offset);
  TRS &rotate(Angle angle);
  TRS &rotate(Angle angle, const Vector2f &center);
  TRS &scale(const Vector2f &f);
  TRS &scale(const Vector2f &f, const Vector2f &center);
};

} // namespace Vexile
