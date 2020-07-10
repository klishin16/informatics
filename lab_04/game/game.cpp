#include <iostream>
#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) :
  field() {
  players.push_back(first);
  players.push_back(second);
}
void game_t::show_field() {
    std::cout << "  A|B|C|D|E|F|G|H" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << i + 1 << '|';
        for (int j = 0; j < 8; j++) {
            if (!field.deck[i][j].m_is_empty) {
                char c;
                if (!field.deck[i][j].m_is_king) {
                    c = field.deck[i][j].m_side == 0 ? 'b' : 'w';
                } else {
                    c = field.deck[i][j].m_side == 0 ? 'B' : 'W';
                }
                std::cout << c;
            } else {
                std::cout << '.';
            }
            std::cout << '|';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool game_t::is_king(const step_t &step, int side) const {
    if (side == 0) { //BLACK
        return step.to.y == 7;
    } else {
        return step.to.y == 0;
    }
}

bool game_t::is_next_step(const step_t &step, int side) {
    if (!field.deck[step.to.y][step.to.x].m_is_king) {
        return game_t::is_next_standard_step(step, side);
    }
    else {
        return game_t::is_next_king_step(step, side);
    }
}

bool game_t::is_next_standard_step(const step_t &step, int side) {
    if ((step.to.x + 2 < 8) && (step.to.y + 2 < 8)) {
        if ((!field.deck[step.to.y + 1][step.to.x + 1].m_is_empty) && (field.deck[step.to.y + 1][step.to.x + 1].m_side != side)) {
            if (field.deck[step.to.y + 2 ][step.to.x + 2].m_is_empty) {
                return true;
            }
        }
    }
    if ((step.to.x + 2 < 8) && (step.to.y - 2 >= 0)) {
        if ((!field.deck[step.to.y - 1][step.to.x + 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x + 1].m_side != side)) {
            if (field.deck[step.to.y - 2 ][step.to.x + 2].m_is_empty) {
                return true;
            }
        }
    }
    if ((step.to.x - 2 >= 0) && (step.to.y + 2 < 8)) {
        if ((!field.deck[step.to.y + 1][step.to.x - 1].m_is_empty) && (field.deck[step.to.y + 1][step.to.x -1].m_side != side)) {
            if (field.deck[step.to.y + 2 ][step.to.x - 2].m_is_empty) {
                return true;
            }
        }
    }
    if ((step.to.x - 2 >= 0) && (step.to.y - 2 >= 0)) {
        if ((!field.deck[step.to.y - 1][step.to.x - 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x -1].m_side != side)) {
            if (field.deck[step.to.y - 2 ][step.to.x - 2].m_is_empty) {
                return true;
            }
        }
    }
    return false;
}

bool game_t::is_next_king_step(const step_t &step, int side) {
    int x = step.to.y;
    int y = step.to.x;
    std::vector<int> steck;
    std::vector<int> templ = {0, 1, 0};
    while(x < 8 && y < 8) {
        if (field.deck[y][x].m_is_empty) {
            steck.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            steck.push_back(1);
        } else {
            steck.push_back(-1);
        }
        x++;
        y++;
    }
    auto res = search(begin(steck), end(steck), begin(templ), end(templ));
    if (res != end(steck)) {
        return true;
    }

    x = step.to.x;
    y = step.to.y;
    std::vector<int> stack2;
    while(x < 8 && y >= 0) {
        if (field.deck[y][x].m_is_empty) {
            stack2.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack2.push_back(1);
        } else {
            stack2.push_back(-1);
        }
        x++;
        y--;
    }
    auto res2 = search(begin(stack2), end(stack2), begin(templ), end(templ));
    if (res2 != end(stack2)) {
        return true;
    }

    x = step.to.x;
    y = step.to.y;
    std::vector<int> stack3;
    while(x >= 0 && y < 8) {
        if (field.deck[y][x].m_is_empty) {
            stack3.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack3.push_back(1);
        } else {
            stack3.push_back(-1);
        }
        x--;
        y++;
    }
    auto res3 = search(begin(stack3), end(stack3), begin(templ), end(templ));
    if (res3 != end(stack3)) {
        return true;
    }

    x = step.to.x;
    y = step.to.y;
    std::vector<int> stack4;
    while(x >= 0 && y >= 0) {
        if (field.deck[y][x].m_is_empty) {
            stack4.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack4.push_back(1);
        } else {
            stack4.push_back(-1);
        }
        x--;
        y--;
    }
    auto res4 = search(begin(stack4), end(stack4), begin(templ), end(templ));
    if (res4 != end(stack4)) {
        return true;
    }
    return false;
}

bool game_t::apply_step(const step_t &step, int side) {
    if(!field.deck[step.from.y][step.from.x].m_is_king) {
        return game_t::apply_standard_step(step, side);
    } else {
        return game_t::apply_king_step(step, side);
    }
}

bool game_t::is_available_standard_step(const step_t &step) {
    return (!field.deck[step.from.y][step.from.x].m_is_empty) && (field.deck[step.to.y][step.to.x].m_is_empty)
           && abs(step.to.x - step.from.x) == abs(step.to.y - step.from.y);
}

bool game_t::is_corect_side(const step_t &step, int side) {
    return field.deck[step.from.y][step.from.x].m_side == side;
}

bool game_t::is_standard_step(const step_t &step, int side) {
    if (!game_t::is_available_kill(step, side)) {
        if ((side == 0 && step.to.y - step.from.y > 0) || (side == 1 && step.to.y - step.from.y < 0)) {
            if (abs(step.from.x - step.to.x) == 1 && abs(step.from.y - step.to.y) == 1) {
                cell_t temp{true};
                field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                field.deck[step.from.y][step.from.x] = temp;
                return true;
            }
        }
    }
    return false;
}

bool game_t::is_king_standard_step(const step_t &step, int side) {
    if (!game_t::is_available_kill(step, side)) {
        if (abs(step.from.x - step.to.x) == 1 && abs(step.from.y - step.to.y) == 1) {
            cell_t temp{true};
            field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
            field.deck[step.from.y][step.from.x] = temp;
            return true;
        }
    }
    return false;
}

bool game_t::is_standard_kill(const step_t &step, int side) {
    if (abs(step.from.x - step.to.x) == 2 && abs(step.from.y - step.to.y) == 2) {
        if (!field.deck[(step.to.y + step.from.y)/2][(step.to.x + step.from.x)/2].m_is_empty) {
            if (field.deck[(step.to.y + step.from.y)/2][(step.to.x + step.from.x)/2].m_side != side) {
                cell_t temp {true};
                field.deck[(step.to.y + step.from.y)/2][(step.to.x + step.from.x)/2] = temp;
                field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                field.deck[step.from.y][step.from.x] = temp;
                return true;
            }
        }
    }
    return false;
}

bool game_t::is_available_kill(const step_t &step, int side) {
    bool flag = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((!field.deck[j][i].m_is_empty) && (field.deck[j][i].m_side == side)) {
                if (game_t::search_kill(point_t(i, j), field, side)) {
                    flag = true;
                    break;
                }
            }
        }
        if (flag) break;
    }
    return flag;
}

bool game_t::search_kill(point_t t, const field_t &field, int side) {
    if (field.deck[t.y][t.x].m_is_king) {
        return game_t::king_check_kill(t, field, side);
    } else {
        return game_t::check_kill(t, field, side);
    }
}

bool game_t::apply_standard_step(const step_t &step, int side) {
    if (game_t::is_corect_side(step, side) && game_t::is_available_standard_step(step)) {
        //std::cout << "Point";
        if (field.deck[step.from.y][step.from.x].m_is_king) {
            if (game_t::is_king_standard_step(step, side)) return true;
            else if (game_t::is_standard_kill(step, side)) return true;
        } else {
            if (game_t::is_standard_step(step, side)) return true;
            else if (game_t::is_standard_kill(step, side)) return true;
        }
    }
    return false;
}

bool game_t::apply_king_step(const step_t &step, int side) {
    if (field.deck[step.to.y][step.to.x].m_is_empty) {
        if ((abs(step.to.x - step.from.x) <= 2 || (abs(step.to.y - step.from.y) <= 2))) {
            return game_t::apply_standard_step(step, side);
        } else {
            if (step.to.x - step.from.x > 0) {
                if (step.to.y - step.from.y > 0) {
                    if((!field.deck[step.to.y - 1][step.to.x - 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x - 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y - 1][step.to.x - 1] = a;
                        return true;
                    }
                } else {
                    if((!field.deck[step.to.y + 1][step.to.x - 1].m_is_empty) && (field.deck[step.to.y + 1][step.to.x - 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y + 1][step.to.x - 1] = a;
                        return true;
                    }
                }
            }
            if (step.to.x - step.from.x < 0) {
                if (step.to.y - step.from.y > 0) {
                    if((!field.deck[step.to.y - 1][step.to.x + 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x + 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y - 1][step.to.x + 1] = a;
                        return true;
                    }
                } else {
                    if ((!field.deck[step.to.y + 1][step.to.x + 1].m_is_empty) &&
                        (field.deck[step.to.y + 1][step.to.x + 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y + 1][step.to.x + 1] = a;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

game_t::game_outcome_t game_t::is_win(bool no_steps) const {
    if (no_steps) {
        return NO_STEPS;
    }
    int white_count = 0;
    int black_count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j ++) {
            if (!field.deck[i][j].m_is_empty) {
                if(field.deck[i][j].m_side == 0) {
                    black_count++;
                } else {
                    white_count++;
                }
            }
        }
    }
    if (white_count == 0 || black_count == 0) {
        return WIN;
    }
    return IN_PROGRESS;
}

void game_t::play() {
  size_t counter = 0;
  bool no_steps = false;
  while (is_win(no_steps) == IN_PROGRESS) {
    counter = (counter + 1) % 2;
    bool is_correct = false;
    bool is_next = false;

    point_t p {0, 0};
    step_t step1 {p, p};
    do {
        if (is_next) {
            is_correct = false;
        }
        while (!is_correct) {
            step_t step = players[counter]->make_step(field, counter);

            if (step.from.x == -1) { // NO STEPS
                no_steps = true;
                is_correct = true;
                continue;
            }

            is_correct = apply_step(step, counter);
            std::cout << "Is step correct: " << is_correct << std::endl;
            if (!is_correct) {
                players[counter]->on_incorrect_step(step, counter);
            }
            //Проверка на дамку
            if (is_king(step, counter)) {
                field.deck[step.to.y][step.to.x].m_is_king = true;
            }
            step1 = step;
        }

        if (abs(step1.from.x - step1.to.x) >= 2 && abs(step1.from.y - step1.to.y) >= 2) {
            is_next = is_next_step(step1, counter);
        } else {
            is_next = false;
        }
        game_t::show_field();
    } while (is_next);
  }
  std::cout << "\n \n \nGAME OVER!!!" << std::endl;

  for (size_t i = 0; i < players.size(); ++i) {
      if (game_t::is_win(no_steps) != NO_STEPS) {
          if (i == counter) {
              players[i]->on_win();
          } else {
              players[i]->on_lose();
          }
      } else {
          if (i == counter) {
              players[i]->on_lose();
          } else {
              players[i]->on_win();
          }
      }

  }
}

bool game_t::check_kill(point_t t, const field_t &fld, int side) {
    if ((t.x + 2 < 8) && (t.y + 2 < 8)) {
        if (!(fld.deck[t.y + 1][t.x + 1].m_is_empty) && (fld.deck[t.y + 2][t.x + 2].m_is_empty)) {
            if (fld.deck[t.y + 1][t.x + 1].m_side != side) {
                return true;
            }
        }
    }
    if ((t.x + 2 < 8) && (t.y - 2 >= 0)) {
        if (!(fld.deck[t.y - 1][t.x + 1].m_is_empty) && (fld.deck[t.y - 2][t.x + 2].m_is_empty)) {
            if (fld.deck[t.y - 1][t.x + 1].m_side != side) {
                return true;
            }
        }
    }
    if ((t.x - 2 >= 0) && (t.y + 2 < 8)) {
        if (!(fld.deck[t.y + 1][t.x - 1].m_is_empty) && (fld.deck[t.y + 2][t.x - 2].m_is_empty)) {
            if (fld.deck[t.y + 1][t.x - 1].m_side != side) {
                return true;
            }
        }
    }
    if ((t.x - 2 >= 0) && (t.y - 2 >= 0)) {
        if (!(fld.deck[t.y - 1][t.x - 1].m_is_empty) && (fld.deck[t.y - 2][t.x - 2].m_is_empty)) {
            if (fld.deck[t.y - 1][t.x - 1].m_side != side) {
                return true;
            }
        }
    }
    return false;
}

bool game_t::king_check_kill(point_t t, const field_t &field, int side) {
    int x = t.x;
    int y = t.y;
    std::vector<int> stack1;
    std::vector<int> templ = {0, 1, 0};
    while(x < 8 && y < 8) {
        if (field.deck[y][x].m_is_empty) {
            stack1.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack1.push_back(1);
        } else {
            stack1.push_back(-1);
        }
        x++;
        y++;
    }
    auto res1 = search(begin(stack1), end(stack1), begin(templ), end(templ));
    if (res1 != end(stack1)) {
        return true;
    }

    x = t.x;
    y = t.y;
    std::vector<int> stack2;
    while(x < 8 && y >= 0) {
        if (field.deck[y][x].m_is_empty) {
            stack2.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack2.push_back(1);
        } else {
            stack2.push_back(-1);
        }
        x++;
        y--;
    }
    auto res2 = search(begin(stack2), end(stack2), begin(templ), end(templ));
    if (res2 != end(stack2)) {
        return true;
    }

    x = t.x;
    y = t.y;
    std::vector<int> stack3;
    while(x >= 0 && y < 8) {
        if (field.deck[y][x].m_is_empty) {
            stack3.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack3.push_back(1);
        } else {
            stack3.push_back(-1);
        }
        x--;
        y++;
    }
    auto res3 = search(begin(stack3), end(stack3), begin(templ), end(templ));
    if (res3 != end(stack3)) {
        return true;
    }

    x = t.x;
    y = t.y;
    std::vector<int> stack4;
    while(x >= 0 && y >= 0) {
        if (field.deck[y][x].m_is_empty) {
            stack4.push_back(0);
        } else if (field.deck[y][x].m_side != side) {
            stack4.push_back(1);
        } else {
            stack4.push_back(-1);
        }
        x--;
        y--;
    }
    auto res4 = search(begin(stack4), end(stack4), begin(templ), end(templ));
    if (res4 != end(stack4)) {
        return true;
    }
    return false;
}
