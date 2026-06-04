#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::Event;
using game::IPlayer;
using game::Point;
using game::Sign;
using game::State;

class MyPlayer : public IPlayer {
  Sign m_sign = Sign::NONE;
  const char *m_name;

public:
  MyPlayer(const char *name) : m_sign(Sign::NONE), m_name(name) {}
  void set_sign(Sign sign) override;
  Point make_move(const State &game) override;
  const char *get_name() const override;
};

// ==================== DECLARATIONS FOR UNIT TESTS ====================
int count_in_direction(const State& state, int x, int y, int dx, int dy, Sign sign);
int score_for_count(int count);
int evaluate_cell(const State& state, int x, int y, Sign sign);
bool is_winning_move(const State& state, int x, int y, Sign sign);

}; // namespace ttt::my_player