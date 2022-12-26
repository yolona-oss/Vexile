#include "Vexile/Core/System/VCharBuffer.hpp"

namespace Vexile {

bool VCharBuffer::getline(const unsigned i, std::string &ret) {
  ret.clear();
  for (unsigned col = 0, row = 0; col < this->size(); col++) {
    ret.append(sizeof(char), this->at(col));
    if (this->at(col) == '\n') {
      if (row == i) {
        return true;
      }
      ret.clear();
      row++;
    }
  }

  return false;
};

/* get defined chars from start to end in line line_n
 * return count of writen chars */
int VCharBuffer::getline(const unsigned line_n, const unsigned start, const unsigned end,
                         std::string &ret) {
  ret.clear();
  if (start > end) {
    throw std::runtime_error(
        eprintf("charVectorBuffer::", __func__, " Cant read chars from: ", start, " to: ", end));
  } else if (start == end) { /* one char need */
    ret.append(1, this->at(start));
    return 1;
  }

  std::string source;
  if (!this->getline(line_n, source)) {
    return 0;
  }

  int readed = 0;
  for (int col = start; col < end && col < source.length(); col++, readed++) {
    ret.append(1, source[col]);
  }

  return readed;
}

int VCharBuffer::getline(const unsigned line_n, const start_end<unsigned> s_e, std::string &ret) {
  return getline(line_n, s_e.start, s_e.end, ret);
}

VCharBuffer &VCharBuffer::addline(const std::string &s) {
  int c;
  for (c = 0; c < s.length(); c++) {
    this->push_back(s.at(c));
  }
  if (s.at(c) != '\n') {
    this->push_back('\n');
  }
  return *this;
}
VCharBuffer &VCharBuffer::addchar(const char c) {
  this->push_back(c);
  return *this;
}

} // namespace Vexile
