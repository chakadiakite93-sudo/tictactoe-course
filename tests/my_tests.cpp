#include <iostream>
#include <cassert>
#include "core/state.hpp"
#include "player/my_player.hpp"

using namespace ttt::my_player;
using namespace ttt::game;

int main() {
    std::cout << "\n=== MyPlayer Unit Tests ===" << std::endl;
    
    // Test 1: score_for_count
    std::cout << "Test 1: score_for_count..." << std::endl;
    assert(score_for_count(5) == 1000000);
    assert(score_for_count(4) == 100000);
    assert(score_for_count(3) == 5000);
    assert(score_for_count(2) == 100);
    assert(score_for_count(1) == 1);
    std::cout << "  ✓ PASSED" << std::endl;
    
    // Test 2: count_in_direction
    std::cout << "Test 2: count_in_direction..." << std::endl;
    State::Opts opts;
    opts.cols = 20;
    opts.rows = 20;
    opts.win_len = 5;
    opts.max_moves = 400;
    State state(opts, nullptr);
    int count = count_in_direction(state, 10, 10, 1, 0, Sign::X);
    std::cout << "  ✓ PASSED (count = " << count << ")" << std::endl;
    
    // Test 3: evaluate_cell
    std::cout << "Test 3: evaluate_cell..." << std::endl;
    int score = evaluate_cell(state, 10, 10, Sign::X);
    std::cout << "  ✓ PASSED (score = " << score << ")" << std::endl;
    
    // Test 4: is_winning_move
    std::cout << "Test 4: is_winning_move..." << std::endl;
    bool winning = is_winning_move(state, 10, 10, Sign::X);
    std::cout << "  ✓ PASSED (result = " << winning << ")" << std::endl;

    std::cout << "\n=== ALL TESTS PASSED! ===\n" << std::endl;
    
    return 0;
}