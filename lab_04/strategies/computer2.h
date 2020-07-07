#pragma once

#include <string>

#include "../game/structures.h"
#include "computer_interface.h"
#include "computer.h"

class computer_strategy2_t : public computer_interface_t {
public:
    explicit computer_strategy2_t(std::string name);
    step_t make_step(const field_t &field, int side) override;
    void print_stat() const override;

private:
    std::string name;
    step_t search_kill(point_t t, const field_t &field, int side);
    step_t king_check_kill(point_t t, const field_t &field, int side);
    step_t check_kill (point_t t, const field_t &fld, int side);

    std::vector<step_t> available_steps (point_t t, const field_t &fld, bool is_king, int side);
    std::vector<step_t> standard_available_steps (point_t t, const field_t &fld, int side);
    static std::vector<step_t> king_available_steps (point_t t, const field_t &fld, int side);

    step_t make_step_black (const field_t &fld, int side);
    step_t make_step_white (const field_t &fld, int side);
};


