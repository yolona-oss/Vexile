#pragma once

namespace Vexile {

struct BasicLinePosition {
  BasicLinePosition(int r = 0, int c = 0) : _row(r), _col(c) {}
  int _row;
  int _col;
};

class LinePosition : BasicLinePosition {
public:
  LinePosition(int r = 0, int c = 0);
  LinePosition(const LinePosition &);
  LinePosition(const LinePosition &&);

  LinePosition &operator=(const LinePosition &other);
  LinePosition &operator=(const LinePosition &&other);

  LinePosition &addRow(int c = 1);
  LinePosition &addCol(int c = 1);

  int row() const;
  int col() const;

private:
  using BasicLinePosition::_col;
  using BasicLinePosition::_row;
};

bool operator==(const LinePosition &left, const LinePosition &right);
bool operator!=(const LinePosition &left, const LinePosition &right);
bool operator>(const LinePosition &left, const LinePosition &right);
bool operator<(const LinePosition &left, const LinePosition &right);
bool operator>=(const LinePosition &left, const LinePosition &right);
bool operator<=(const LinePosition &left, const LinePosition &right);

} // namespace Vexile
