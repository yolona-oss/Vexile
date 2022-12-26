#include "Vexile/Core/System/Formatter.hpp"

#include <algorithm>

namespace Vexile {

std::string Formatter::toLower(const std::string &str) {
  std::string ret(str);

  std::transform(ret.begin(), ret.end(), ret.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  return ret;
}

std::string Formatter::toUpper(const std::string &str) {
  std::string ret(str);

  std::transform(ret.begin(), ret.end(), ret.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  return ret;
}

std::string Formatter::trim(const std::string &str) {
  size_t startPos = str.find_first_not_of(" \t");
  if (startPos == std::string::npos)
    return "";
  size_t endPos = str.find_last_not_of(" \t");
  return str.substr(startPos, endPos - startPos + 1);
}

template <typename T> std::string Formatter::toHex(T value, bool include0x) {
  std::stringstream stream;
  stream << (include0x ? "0x" : "") << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex
         << value;
  return stream.str();
}

} // namespace Vexile
