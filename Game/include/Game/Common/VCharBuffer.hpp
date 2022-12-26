#pragma once

#include "Vexile/Core/Error/eprintf.hpp"
#include <string>
#include <vector>

namespace Vexile {

template <typename T> struct start_end {
  T start, end;
  T diff() const { return end - start; }
  start_end() : start_end(0, 0) {}
  start_end(T s, T e) : start(s), end(e) {}
};

class VCharBuffer : public std::vector<char> {
public:
  bool getline(const unsigned i, std::string &ret);

  /* get defined chars from start to end in line line_n
   * return count of writen chars */
  int getline(const unsigned line_n, const unsigned start, const unsigned end, std::string &ret);
  int getline(const unsigned line_n, const start_end<unsigned> s_e, std::string &ret);
  VCharBuffer &addline(const std::string &s);
  VCharBuffer &addchar(const char c);
};

} // namespace Vexile
