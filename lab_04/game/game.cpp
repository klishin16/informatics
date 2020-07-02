#include <iostream>
#include "game.h"
#include "windows.h"

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
    std::cout << "Check next step!" << std::endl;
    if (!field.deck[step.to.y][step.to.x].m_is_king) {
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
    } else {
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

bool game_t::apply_standard_step(const step_t &step, int side) {
    if ((!field.deck[step.from.y][step.from.x].m_is_empty ) && (field.deck[step.to.y][step.to.x].m_is_empty)){
        if (abs(step.from.x - step.to.x) == 2 && abs(step.from.y - step.to.y) == 2) {
            //удар
            std::cout << "Kill" << std::endl;
            cell_t temp {true};
            field.deck[(step.to.y + step.from.y)/2][(step.to.x + step.from.x)/2] = temp;
        }
        cell_t temp {true};
        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
        field.deck[step.from.y][step.from.x] = temp;
        return true;
    } else {
        return false;
    }
}

bool game_t::apply_king_step(const step_t &step, int side) {
    if (field.deck[step.to.y][step.to.x].m_is_empty) {
        if ((abs(step.to.x - step.from.x) <= 2 || (abs(step.to.y - step.from.y) <= 2))) {
            return game_t::apply_standard_step(step, side);
        } else {
            if (step.to.x - step.from.x > 0) {
                if (step.to.y - step.from.y > 0) {
                    std::cout << "Apply king step 1!" << std::endl;
                    if((!field.deck[step.to.y - 1][step.to.x - 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x - 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y - 1][step.to.x - 1] = a;
                        return true;
                    }
                } else {
                    std::cout << "Apply king step 2!" << std::endl;
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
                    std::cout << "Apply king step 3!" << std::endl;
                    if((!field.deck[step.to.y - 1][step.to.x + 1].m_is_empty) && (field.deck[step.to.y - 1][step.to.x + 1].m_side != side)) {
                        cell_t a = {true};
                        field.deck[step.to.y][step.to.x] = field.deck[step.from.y][step.from.x];
                        field.deck[step.from.y][step.from.x] = a;
                        field.deck[step.to.y - 1][step.to.x + 1] = a;
                        return true;
                    }
                } else {
                    std::cout << "Apply king step 4!" << std::endl;
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
    std::cout << "Apply king step (no)!" << std::endl;
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
        if (no_steps) {
            std::cout << "MDA" << std::endl;
        }
        if (abs(step1.from.x - step1.to.x) == 2 && abs(step1.from.y - step1.to.y) == 2) {
            is_next = is_next_step(step1, counter);
        }
        std::cout << "Is_next_step: " << is_next << std::endl;
        game_t::show_field();
        //Sleep(500);
    } while (is_next);
      std::cout << "Counter++ : " << counter << std::endl;
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
