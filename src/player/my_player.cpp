#include "my_player.hpp"
#include <climits>
#include <cmath>
#include <cstdlib>

namespace ttt::my_player {

const char* MyPlayer::get_name() const {
    return "ChakaBot";
}

void MyPlayer::set_sign(Sign sign) {
    m_sign = sign;
}

// ==================== count_in_direction ====================
int count_in_direction(const State& state, int x, int y, int dx, int dy, Sign sign) {
    int count = 1;
    int cols = state.get_opts().cols;
    int rows = state.get_opts().rows;
    
    for (int step = 1; step <= 4; step++) {
        int nx = x + dx * step;
        int ny = y + dy * step;
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) break;
        if (state.get_value(nx, ny) == sign) count++;
        else break;
    }
    
    for (int step = 1; step <= 4; step++) {
        int nx = x - dx * step;
        int ny = y - dy * step;
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) break;
        if (state.get_value(nx, ny) == sign) count++;
        else break;
    }
    
    return count;
}

// ==================== score_for_count ====================
int score_for_count(int count) {
    if (count >= 5) return 1000000;
    if (count == 4) return 100000;
    if (count == 3) return 5000;
    if (count == 2) return 100;
    return 1;
}

// ==================== evaluate_cell ====================
int evaluate_cell(const State& state, int x, int y, Sign sign) {
    int total = 0;
    int dirs[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    
    for (int i = 0; i < 4; i++) {
        int count = count_in_direction(state, x, y, dirs[i][0], dirs[i][1], sign);
        total += score_for_count(count);
    }
    return total;
}

// ==================== is_winning_move ====================
bool is_winning_move(const State& state, int x, int y, Sign sign) {
    int dirs[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
    int cols = state.get_opts().cols;
    int rows = state.get_opts().rows;
    
    for (int d = 0; d < 4; d++) {
        int count = 1;
        
        for (int step = 1; step <= 4; step++) {
            int nx = x + dirs[d][0] * step;
            int ny = y + dirs[d][1] * step;
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) break;
            if (state.get_value(nx, ny) == sign) count++;
            else break;
        }
        
        for (int step = 1; step <= 4; step++) {
            int nx = x - dirs[d][0] * step;
            int ny = y - dirs[d][1] * step;
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) break;
            if (state.get_value(nx, ny) == sign) count++;
            else break;
        }
        
        if (count >= 5) return true;
    }
    return false;
}

// ==================== make_move ====================
Point MyPlayer::make_move(const State& state) {
    Point best_move = {0, 0};
    int best_score = INT_MIN;
    int cols = state.get_opts().cols;
    int rows = state.get_opts().rows;
    Sign opponent = (m_sign == Sign::X) ? Sign::O : Sign::X;
    
    // first priority : win immediately
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            if (state.get_value(x, y) == Sign::NONE) {
                if (is_winning_move(state, x, y, m_sign)) {
                    return {x, y};
                }
            }
        }
    }
    
    // second priority : block opponent
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            if (state.get_value(x, y) == Sign::NONE) {
                if (is_winning_move(state, x, y, opponent)) {
                    return {x, y};
                }
            }
        }
    }
    
    // third : Heuristic
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            if (state.get_value(x, y) == Sign::NONE) {
                int attack = evaluate_cell(state, x, y, m_sign);
                int defense = evaluate_cell(state, x, y, opponent);
                int center_x = cols / 2;
                int center_y = rows / 2;
                int bonus = 20 - (abs(x - center_x) + abs(y - center_y));
                
                int score = (attack * 4) + (defense * 2) + bonus;
                
                if (score > best_score) {
                    best_score = score;
                    best_move = {x, y};
                }
            }
        }
    }
    return best_move;
}

} // namespace ttt::my_player