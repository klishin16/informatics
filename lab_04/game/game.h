#pragma once

#include <memory>
#include <vector>

#include "../strategies/interface.h"
#include "structures.h"

class game_t {
public:
  using player_t = std::shared_ptr<strategy_interface_t>;
  game_t(const player_t &first, const player_t &second);

  void play();
  void show_field();

  enum game_side_t {
      BLACK,
      WHITE
  };

private:
  enum game_outcome_t {
    WIN,
    NO_STEPS,
    IN_PROGRESS
  };
  bool is_king(const step_t &step, int side) const;

  game_outcome_t is_win(bool no_steps) const;

  bool apply_step(const step_t &step, int side);

  bool apply_standard_step(const step_t &step, int side);

  bool apply_king_step(const step_t &step, int side);

  bool is_next_step(const step_t &step, int side);

  bool is_next_standard_step(const step_t &step, int side);

  bool is_next_king_step(const step_t &step, int side);

    field_t field;
    std::vector<player_t> players;
};

