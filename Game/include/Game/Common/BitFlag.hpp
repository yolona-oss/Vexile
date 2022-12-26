#pragma once

#include <cstdint>
#include <utility>

// NOTE not safe
namespace Vexile {

typedef uint8_t bitflag8_t;
typedef uint16_t bitflag16_t;
typedef uint32_t bitflag32_t;
typedef uint64_t bitflag64_t;
typedef uint8_t bitflag_t;

template <typename Cap, int Zero = 0> class BitFlag {
public:
  BitFlag(Cap state = Zero) : _flag(state) {}
  BitFlag(const BitFlag &bf) : BitFlag(bf._flag) {}
  BitFlag(const BitFlag &&bf) : BitFlag(bf._flag) {}
  virtual ~BitFlag() {}

  BitFlag &set(Cap f) {
    _flag |= f;
    return *this;
  }
  BitFlag &remove(Cap f) {
    _flag &= ~f;
    return *this;
  }
  bool isSetted(Cap f) const {
    if ((_flag & f) == f)
      return true;
    return false;
  }
  const Cap raw() const { return _flag; };
  BitFlag &clean() {
    _flag = Zero;
    return *this;
  }

  operator Cap() { return _flag; }

  BitFlag &operator=(const Cap &flag) {
    _flag = flag;
    return *this;
  }
  BitFlag &operator=(const BitFlag &&other) {
    _flag = other._flag;
    return *this;
  }
  BitFlag &operator=(const BitFlag &other) {
    _flag = other._flag;
    return *this;
  }

protected:
  Cap _flag;
};

template <typename T, int Zero>
bool operator==(const BitFlag<T, Zero> &left, const BitFlag<T, Zero> right) {
  return left.raw() == right.raw();
}

template <typename T, int Zero>
bool operator!=(const BitFlag<T, Zero> &left, const BitFlag<T, Zero> right) {
  return left.raw() != right.raw();
}

} // namespace Vexile
