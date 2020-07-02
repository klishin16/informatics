#pragma once

#include <algorithm>
#include <vector>
#include <iostream>


struct point_t {
    point_t(int x, int y): x{x}, y{y} {}
    int x;
    int y;
};
class Place {

public:
    bool m_is_empty = true;
    int m_side;
    bool m_is_king = false;
    Place(int side): m_side(side) {
        m_is_empty = false;
    };
    bool isEmpty() const { return m_is_empty; }
    int getSide() const { return m_side; }
    bool isKing() const { return m_is_king; }
    Place() {

    };
};

struct cell_t {
    bool m_is_empty = true;
    int m_side;
    bool m_is_king = false;
    cell_t(bool is_empty): m_is_empty(is_empty) {};
};

struct step_t {
    point_t from, to;
  step_t(point_t from, point_t to):
    from{from}, to{to} {}
  int x, y;
};

struct field_t {
  field_t() {
      for (int i = 0; i < 8; i++) {
          std::vector<cell_t> row;
          for (int j = 0; j < 8; j++) {
              if (fld[i][j] == '.') {
                  cell_t temp {true};
                  row.push_back(temp);
              } else {
                  cell_t temp2 = {false};
                  temp2.m_side = fld[i][j] == 'b' ? 0 : 1;
                  row.push_back(temp2);
              }
          }
          deck.push_back(row);
      }
  }

  const size_t size = 8;
  std::vector<std::vector<cell_t>> deck;

  char fld[8][8] = {{'.', 'b', '.', 'b', '.', 'b', '.', 'b'},
                    {'b', '.', 'b', '.', 'b', '.', 'b', '.'},
                    {'.', 'b', '.', 'b', '.', 'b', '.', 'b'},
                    {'.', '.', '.', '.', '.', '.', '.', '.'},
                    {'.', '.', '.', '.', '.', '.', '.', '.'},
                    {'w', '.', 'w', '.', 'w', '.', 'w', '.'},
                    {'.', 'w', '.', 'w', '.', 'w', '.', 'w'},
                    {'w', '.', 'w', '.', 'w', '.', 'w', '.'}};



};
