#include "minesweeper.h"
#include <algorithm>
#include <random>
#include <queue>

std::vector<std::pair<size_t, size_t>> Neighbours(size_t y, size_t x, size_t max_y, size_t max_x) {
    std::vector<std::pair<size_t, size_t>> neighbours;
    if (!y && !x) {
        for (size_t i = 1; i < 4; ++i) {
            neighbours.push_back({i / 2, i % 2});
        }
    } else if (!y && x == max_x - 1) {
        for (size_t i = 0; i < 4; ++i) {
            if (i != 1) {
                neighbours.push_back({i / 2, x + i % 2 - 1});
            }
        }
    } else if (!x && y == max_y - 1) {
        for (size_t i = 0; i < 4; ++i) {
            if (i != 2) {
                neighbours.push_back({y + i / 2 - 1, i % 2});
            }
        }
    } else if (y == max_y - 1 && x == max_x - 1) {
        for (size_t i = 0; i < 4; ++i) {
            if (i != 3) {
                neighbours.push_back({y + i / 2 - 1, x + i % 2 - 1});
            }
        }
    } else if (!y) {
        for (size_t i = 0; i < 6; ++i) {
            if (i != 1) {
                neighbours.push_back({i / 3, x + i % 3 - 1});
            }
        }
    } else if (!x) {
        for (size_t i = 0; i < 6; ++i) {
            if (i != 2) {
                neighbours.push_back({y + i / 2 - 1, i % 2});
            }
        }
    } else if (y == max_y - 1) {
        for (size_t i = 0; i < 6; ++i) {
            if (i != 4) {
                neighbours.push_back({y + i / 3 - 1, x + i % 3 - 1});
            }
        }
    } else if (x == max_x - 1) {
        for (size_t i = 0; i < 6; ++i) {
            if (i != 3) {
                neighbours.push_back({y + i / 2 - 1, x + i % 2 - 1});
            }
        }
    } else {
        for (size_t i = 0; i < 9; ++i) {
            if (i != 4) {
                neighbours.push_back({y + i / 3 - 1, x + i % 3 - 1});
            }
        }
    }
    return neighbours;
}

size_t CountMinesAround(size_t y, size_t x, const std::vector<std::vector<char>>& field) {
    size_t mines_cnt = 0;
    auto neighbours = Neighbours(y, x, field.size(), field[0].size());

    for (const auto& elem : neighbours) {
        if (field[elem.first][elem.second] == '*') {
            mines_cnt++;
        }
    }
    return mines_cnt;
}

void FillField(std::vector<std::vector<char>>& field) {
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j) {
            if (field[i][j] != '*') {
                auto mines_cnt = CountMinesAround(i, j, field);
                if (mines_cnt) {
                    field[i][j] = static_cast<char>(mines_cnt + 48);
                } else {
                    field[i][j] = '.';
                }
            }
        }
    }
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    cur_field_.clear();
    cur_field_.resize(height);
    for (auto& row : cur_field_) {
        row = std::vector<char>(width, '-');
    }
    field_ = cur_field_;

    std::vector<size_t> potential_mines(width * height);
    for (size_t i = 0; i < potential_mines.size(); ++i) {
        potential_mines[i] = i;
    }
    auto rng = std::default_random_engine();
    std::shuffle(potential_mines.begin(), potential_mines.end(), rng);

    for (size_t i = 0; i < mines_count; ++i) {
        field_[potential_mines[i] / width][potential_mines[i] % width] = '*';
    }
    FillField(field_);

    game_status_ = GameStatus::NOT_STARTED;
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    cur_field_.clear();
    cur_field_.resize(height);
    for (auto& row : cur_field_) {
        row = std::vector<char>(width, '-');
    }
    field_ = cur_field_;

    for (auto cur_cell : cells_with_mines) {
        field_[cur_cell.y][cur_cell.x] = '*';
    }
    FillField(field_);

    game_status_ = GameStatus::NOT_STARTED;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    Minesweeper::NewGame(width, height, mines_count);
    mines_count_ = mines_count;
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    Minesweeper::NewGame(width, height, cells_with_mines);
    mines_count_ = cells_with_mines.size();
}

Minesweeper::GameStatus OpenThisCell(size_t y, size_t x, std::vector<std::vector<char>>& cur_field,
                                     std::vector<std::vector<char>>& field, size_t& opened_cells) {
    if (field[y][x] == '*') {
        return Minesweeper::GameStatus::DEFEAT;
    }

    std::queue<std::pair<size_t, size_t>> neighbours_without_mines;
    neighbours_without_mines.push({y, x});
    while (!neighbours_without_mines.empty()) {
        auto cur_cell = neighbours_without_mines.front();
        neighbours_without_mines.pop();

        if (cur_field[cur_cell.first][cur_cell.second] == '-') {
            opened_cells++;
        }
        cur_field[cur_cell.first][cur_cell.second] = field[cur_cell.first][cur_cell.second];
        if (cur_field[cur_cell.first][cur_cell.second] == '.') {
            auto neighbours = Neighbours(cur_cell.first, cur_cell.second, field.size(), field[0].size());
            for (const auto& elem : neighbours) {
                if (cur_field[elem.first][elem.second] == '-') {
                    neighbours_without_mines.push({elem.first, elem.second});
                }
            }
        }
    }
    return Minesweeper::GameStatus::IN_PROGRESS;
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (game_status_ == GameStatus::NOT_STARTED) {
        time_ = std::time(nullptr);
    }
    if (game_status_ != GameStatus::DEFEAT && game_status_ != GameStatus::VICTORY) {
        if (cur_field_[cell.y][cell.x] == '-') {
            game_status_ = OpenThisCell(cell.y, cell.x, cur_field_, field_, opened_cells_cnt_);
        }
        if (game_status_ == GameStatus::DEFEAT) {
            cur_field_ = field_;
        }
    }
    if (mines_count_ + opened_cells_cnt_ == cur_field_.size() * cur_field_[0].size()) {
        game_status_ = GameStatus::VICTORY;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (game_status_ != GameStatus::DEFEAT && game_status_ != GameStatus::VICTORY) {
        if (cur_field_[cell.y][cell.x] != '?') {
            cur_field_[cell.y][cell.x] = '?';
        } else {
            cur_field_[cell.y][cell.x] = '-';
        }
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    if (time_ == 0) {
        return 0;
    } else {
        return (std::time(nullptr) - time_);
    }
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    Minesweeper::RenderedField result(cur_field_.size());
    for (size_t i = 0; i < cur_field_.size(); ++i) {
        for (const auto& elem : cur_field_[i]) {
            result[i] += elem;
        }
    }
    return result;
}
