#pragma once

#include "../game/structures.h"

class strategy_interface_t {
public:
  virtual step_t make_step(const field_t &field, int side) = 0;
  virtual void on_incorrect_step(const step_t &step, int side) const = 0;

  virtual void on_lose() = 0;
  virtual void on_win() = 0;
  virtual void on_tie() = 0;
};
