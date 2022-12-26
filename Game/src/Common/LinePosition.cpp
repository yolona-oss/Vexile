#include "Vexile/Core/System/LinePosition.hpp"

namespace Vexile {

LinePosition::LinePosition(int r, int c) : BasicLinePosition(r, c) {}
LinePosition::LinePosition(const LinePosition &other) : BasicLinePosition(other._row, other._col) {}
LinePosition::LinePosition(const LinePosition &&other)
    : BasicLinePosition(other._row, other._col) {}

LinePosition &LinePosition::operator=(const LinePosition &other) {
  _row = other._row;
  _col = other._col;
  return *this;
}

LinePosition &LinePosition::operator=(const LinePosition &&other) {
  _row = other._row;
  _col = other._col;
  return *this;
}

LinePosition &LinePosition::addRow(int c) {
  _row += c;
  return *this;
}

LinePosition &LinePosition::addCol(int c) {
  _col += c;
  return *this;
}

int LinePosition::row() const { return _row; }
int LinePosition::col() const { return _col; }

bool operator==(const LinePosition &left, const LinePosition &right) {
  return left.row() == right.row() && left.col() == right.col();
}

bool operator!=(const LinePosition &left, const LinePosition &right) { return !(left == right); }

bool operator>(const LinePosition &left, const LinePosition &right) {
  return left.row() > right.row() && left.col() > right.col();
}

bool operator<(const LinePosition &left, const LinePosition &right) {
  return left.row() < right.row() && left.col() < right.col();
}

bool operator>=(const LinePosition &left, const LinePosition &right) {
  return (left == right) || (left > right);
}

bool operator<=(const LinePosition &left, const LinePosition &right) {
  return (left == right) || (left < right);
}

} // namespace Vexile
