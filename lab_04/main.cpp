#include <memory>

#include "game/game.h"
#include "strategies/human.h"
#include "strategies/computer.h"


int main() {
  //auto player1 = std::make_shared<computer_strategy_t>("First player");
  //auto player2 = std::make_shared<computer_strategy_t>("Second player");

  //for (int i = 0; i < 100000; ++i) {
  //  game_t game(player1, player2);
  //  game.play();
  //}

  //player1->print_stat();
  //player2->print_stat();

  auto player1 = std::make_shared<computer_strategy_t>("BLACK");
  auto player2 = std::make_shared<computer_strategy_t>("WHITE");

  //game_t game(player1, player2);
  //game.show_field();
  //game.play();
  for (int i = 0; i < 14; ++i) {
      game_t game(player1, player2);
      game.play();
  }
  player1->print_stat();
  player2->print_stat();

  return 0;
}
