#pragma once

#include <iomanip>
#include <string>

namespace Vexile {
class Formatter {
public:
  template <typename T> static std::string toHex(T, bool include0x = false);

  static std::string toLower(const std::string &str);
  static std::string toUpper(const std::string &str);

  static std::string trim(const std::string &str);

  virtual ~Formatter();

private:
  Formatter();
};

} // namespace Vexile
