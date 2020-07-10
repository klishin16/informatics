#include "human.h"

#include <algorithm>
#include <iostream>
#include <vector>

void human_strategy_t::on_win() {
  std::cout << "You win!" << std::endl;
}
void human_strategy_t::on_lose() {
  std::cout << "You lose!" << std::endl;
}
void human_strategy_t::on_tie() {
  std::cout << "Tie!" << std::endl;
}

void show_field(const field_t &fld) {

    std::cout << "  A|B|C|D|E|F|G|H" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << i + 1 << '|';
        for (int j = 0; j < 8; j++) {
            if (!fld.deck[i][j].m_is_empty) {
                char c = fld.deck[i][j].m_side == 0 ? 'b' : 'w';
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
point_t normalize_point(char x, int y) {
    std::vector<char > a = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    auto it = std::find(a.begin(), a.end(), x);
    int index = std::distance(a.begin(), it);
    return {index, y - 1};
}

step_t human_strategy_t::make_step(const field_t &fld, int side) {
    show_field(fld);
    std::cout << "Your side is: " << (side == 0 ? "BLACK" : "WHITE") << std::endl;
    std::cout << "Choice chiker: " << std::endl;
    char x1,x2;
    int y1, y2;
    std::cin >> x1 >> y1;
    point_t point1 = normalize_point(x1, y1);

    std::cout << "Choice way: " << std::endl;
    std::cin >> x2 >> y2;
    point_t point2 = normalize_point(x2, y2);
    std::cout << "From x: " << point1.x << " y: "<< point1.y << std::endl;
    std::cout << "To x: " << point2.x << " y: "<< point2.y << std::endl;
    return {point1, point2};
}

void human_strategy_t::on_incorrect_step(const step_t &step, int side) const {
  std::cout << "Incorrect step!" << std::endl;
}

human_strategy_t::human_strategy_t(std::string name) {

}
