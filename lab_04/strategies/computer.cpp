#include "computer.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <random>

step_t computer_strategy_t::search_kill(const point_t t, const field_t &field, int side) {
    if (field.deck[t.y][t.x].m_is_king) {
        return computer_strategy_t::king_check_kill(t, field, side);
    } else {
        return computer_strategy_t::check_kill(t, field, side);
    }
}

step_t computer_strategy_t::check_kill(point_t t, const field_t &fld, int side) {
        if ((t.x + 2 < 8) && (t.y + 2 < 8)) {
            if (!(fld.deck[t.y + 1][t.x + 1].m_is_empty) && (fld.deck[t.y + 2][t.x + 2].m_is_empty)) {
                if (fld.deck[t.y + 1][t.x + 1].m_side != side) {
                    return {t, point_t(t.x + 2, t.y + 2)};
                }
            }
        }
        if ((t.x + 2 < 8) && (t.y - 2 >= 0)) {
            if (!(fld.deck[t.y - 1][t.x + 1].m_is_empty) && (fld.deck[t.y - 2][t.x + 2].m_is_empty)) {
                if (fld.deck[t.y - 1][t.x + 1].m_side != side) {
                    return {t, point_t(t.x + 2, t.y - 2)};
                }
            }
        }
        if ((t.x - 2 >= 0) && (t.y + 2 < 8)) {
            if (!(fld.deck[t.y + 1][t.x - 1].m_is_empty) && (fld.deck[t.y + 2][t.x - 2].m_is_empty)) {
                if (fld.deck[t.y + 1][t.x - 1].m_side != side) {
                    return {t, point_t(t.x - 2, t.y + 2)};
                }
            }
        }
        if ((t.x - 2 >= 0) && (t.y - 2 >= 0)) {
            if (!(fld.deck[t.y - 1][t.x - 1].m_is_empty) && (fld.deck[t.y - 2][t.x - 2].m_is_empty)) {
                if (fld.deck[t.y - 1][t.x - 1].m_side != side) {
                    return {t, point_t(t.x - 2, t.y - 2)};
                }
            }
        }
        return {t, t};
}

step_t computer_strategy_t::king_check_kill(const point_t t, const field_t &field, int side) {
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
        std::cout << "King check kill 1!" << std::endl;
        return {t, point_t(t.x + std::distance(stack1.begin(), res1) + 2, t.y + std::distance(stack1.begin(), res1) + 2)};
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
        std::cout << "King check kill 2!" << std::endl;
        return {t, point_t(t.x + std::distance(stack2.begin(), res2) + 2, t.y - std::distance(stack2.begin(), res2) - 2)};
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
        std::cout << "King check kill 3!" << std::endl;
        return {t, point_t(t.x - std::distance(stack3.begin(), res3) - 2, t.y + std::distance(stack3.begin(), res3) + 2)};
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
        std::cout << "King check kill 4!" << std::endl;
        return {t, point_t(t.x - std::distance(stack4.begin(), res4) - 2, t.y - std::distance(stack4.begin(), res4) - 2)};
    }
    return {t, t};
}

std::vector<step_t> computer_strategy_t::available_steps(point_t t, const field_t &fld, bool is_king, int side) {
    if (!is_king) {
        return computer_strategy_t::standard_available_steps(t, fld, side);
    } else {
        return computer_strategy_t::king_available_steps(t, fld, side);
    }
}

std::vector<step_t> computer_strategy_t::standard_available_steps(point_t t, const field_t &fld, int side) {
    std::vector<step_t> steps;
    if (side == 0) { // BLACK
        if ((t.y + 1 < 8) && (t.x + 1 < 8) && (fld.deck[t.y + 1][t.x + 1].m_is_empty)) {
            steps.push_back(step_t(t, point_t(t.x + 1, t.y + 1)));
        }
        if ((t.y + 1 < 8) && (t.x - 1 >= 0) && (fld.deck[t.y + 1][t.x - 1].m_is_empty)) {
            steps.push_back(step_t(t, point_t(t.x - 1, t.y + 1)));
        }
    } else { // WHITE
        if ((t.y - 1 >= 0) && (t.x + 1 < 8) &&(fld.deck[t.y - 1][t.x + 1].m_is_empty)) {
            steps.push_back(step_t(t, point_t(t.x + 1, t.y - 1)));
        }
        if ((t.y - 1 >= 0) && (t.x - 1 >= 0) && (fld.deck[t.y - 1][t.x - 1].m_is_empty)) {
            steps.push_back(step_t(t, point_t(t.x - 1, t.y - 1)));
        }
    }
    return steps;
}

std::vector<step_t> computer_strategy_t::king_available_steps(point_t t, const field_t &fld, int side) {
    std::vector<step_t> steps;
    if ((t.y + 1 < 8) && (t.x + 1 < 8) && (fld.deck[t.y + 1][t.x + 1].m_is_empty)) {
        steps.push_back(step_t(t, point_t(t.x + 1, t.y + 1)));
    }
    if ((t.y + 1 < 8) && (t.x - 1 >= 0) && (fld.deck[t.y + 1][t.x - 1].m_is_empty)) {
        steps.push_back(step_t(t, point_t(t.x - 1, t.y + 1)));
    }
    if ((t.y - 1 >= 0) && (t.x + 1 < 8) && (fld.deck[t.y - 1][t.x + 1].m_is_empty)) {
        steps.push_back(step_t(t, point_t(t.x + 1, t.y - 1)));
    }
    if ((t.y - 1 >= 0) && (t.x - 1 >= 0) && (fld.deck[t.y - 1][t.x - 1].m_is_empty)) {
        steps.push_back(step_t(t, point_t(t.x - 1, t.y - 1)));
    }
    return steps;
}

computer_strategy_t::computer_strategy_t(std::string name) :
  name(std::move(name)) {}

step_t computer_strategy_t::make_step(const field_t &fld, int side) {
    std::cout << "Computer side:" << name << std::endl;
 if (side == 0) { // BLACK
     return computer_strategy_t::make_step_black(fld, side);
 } else { //WHITE
     return  computer_strategy_t::make_step_white(fld, side);
 }
}

step_t computer_strategy_t::make_step_black(const field_t &fld, int side) {
    std::vector<step_t> all_steps;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if ((!fld.deck[i][j].m_is_empty) && (fld.deck[i][j].m_side == side)) {

                step_t res = computer_strategy_t::search_kill(point_t(j, i), fld, side);
                if (res.to.x != res.from.x) {
                    std::cout << "Computer step (kill): from: \n" << res.from.x+1 << ' ' << res.from.y+1 << " to: " << res.to.x+1 << ' ' << res.to.y+1 << std::endl;
                    return res;
                } else {
                    std::vector<step_t> temp = computer_strategy_t::available_steps(point_t(j, i), fld, fld.deck[i][j].m_is_king, side);
                    all_steps.insert(end(all_steps), temp.begin(), temp.end());
                }
            }
        }
    }
    if (all_steps.size() == 0) {
        std::cout << "Computer step: no steps! " << std::endl;
        return {point_t(-1, -1), point_t(-1, -1)};
    } else {
        std::random_shuffle(all_steps.begin(), all_steps.end());
        std::cout << "Computer step: from: " << all_steps[0].from.x+1 << ' ' << all_steps[0].from.y+1 << " to: " << all_steps[0].to.x+1 << ' ' << all_steps[0].to.y+1 << std::endl;
        return all_steps[0];
    }
}

step_t computer_strategy_t::make_step_white(const field_t &fld, int side) {
    std::vector<step_t> all_steps;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((!fld.deck[j][i].m_is_empty) && (fld.deck[j][i].m_side == side)) {
                step_t res = computer_strategy_t::search_kill(point_t(i, j), fld, side);
                if (res.to.x != res.from.x) {
                    std::cout << "Computer step (kill): from: \n" << res.from.x+1 << ' ' << res.from.y+1 << " to: " << res.to.x+1 << ' ' << res.to.y+1 << std::endl;
                    return res;
                } else {
                    std::vector<step_t> temp = computer_strategy_t::available_steps(point_t(i, j), fld, fld.deck[j][i].m_is_king, side);
                    all_steps.insert(end(all_steps), temp.begin(), temp.end());
                }
            }
        }
    }
    if (all_steps.size() == 0) {
        std::cout << "Computer step: no steps! " << std::endl;
        return {point_t(-1, -1), point_t(-1, -1)};
    } else {
        std::shuffle(all_steps.begin(), all_steps.end(), std::mt19937(std::random_device()()));
        std::cout << "Computer step: from: " << all_steps[0].from.x + 1 << ' ' << all_steps[0].from.y + 1 << " to: "
                  << all_steps[0].to.x + 1 << ' ' << all_steps[0].to.y + 1 << std::endl;
        return all_steps[0];
    }
}

void computer_strategy_t::print_stat() const {
  std::cout << "Random model [" << name << "]: " << std::endl;
  computer_interface_t::print_stat();
}
