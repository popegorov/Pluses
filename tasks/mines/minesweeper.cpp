#include "minesweeper.h"
#include <algorithm>
#include <queue>
#include <random>

std::vector<std::pair<size_t, size_t>> Neighbours(size_t y, size_t x, size_t max_y, size_t max_x) {
    std::vector<std::pair<size_t, size_t>> neighbours;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if ((y + i) > 0 && (y + i - 1) < max_y && (x + j) > 0 && (x + j - 1) < max_x) {
                neighbours.push_back({y + i - 1, x + j - 1});
            }
        }
    }
    return neighbours;
}

size_t CountMinesAround(size_t y, size_t x, const std::vector<std::string>& field) {
    size_t mines_cnt = 0;

    for (const auto& elem : Neighbours(y, x, field.size(), field[0].size())) {
        if (field[elem.first][elem.second] == '*') {
            mines_cnt++;
        }
    }
    return mines_cnt;
}

void FillField(std::vector<std::string>& field) {
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[0].size(); ++j) {
            if (field[i][j] != '*') {
                auto mines_cnt = CountMinesAround(i, j, field);
                if (mines_cnt) {
                    field[i][j] = static_cast<char>(mines_cnt + '0');
                } else {
                    field[i][j] = '.';
                }
            }
        }
    }
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    cur_field_.assign(height, std::string(width, '-'));
    field_ = cur_field_;

    for (auto cur_cell : cells_with_mines) {
        field_[cur_cell.y][cur_cell.x] = '*';
    }
    FillField(field_);

    game_status_ = GameStatus::NOT_STARTED;
    mines_count_ = cells_with_mines.size();
}

std::vector<Minesweeper::Cell> GenerateRandomPlaces(size_t width, size_t height, size_t mines_count) {
    std::vector<size_t> potential_mines(width * height);
    for (size_t i = 0; i < potential_mines.size(); ++i) {
        potential_mines[i] = i;
    }
    auto rng = std::default_random_engine();
    std::shuffle(potential_mines.begin(), potential_mines.end(), rng);

    std::vector<Minesweeper::Cell> result;
    for (size_t i = 0; i < mines_count; ++i) {
        result.push_back({potential_mines[i] % width, potential_mines[i] / width});
    }
    return result;
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, GenerateRandomPlaces(width, height, mines_count));
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

Minesweeper::GameStatus OpenThisCell(size_t y, size_t x, std::vector<std::string>& cur_field,
                                     std::vector<std::string>& field, size_t& opened_cells) {
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

void Minesweeper::StartGame() {
    game_status_ = GameStatus::IN_PROGRESS;
    time_ = time(nullptr);
}

void Minesweeper::StopGame(bool victory) {
    if (victory) {
        game_status_ = GameStatus::VICTORY;
    } else {
        cur_field_ = field_;
    }
    time_ = time(nullptr) - time_;
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (game_status_ == GameStatus::NOT_STARTED) {
        StartGame();
    }
    if (game_status_ != GameStatus::DEFEAT && game_status_ != GameStatus::VICTORY) {
        if (cur_field_[cell.y][cell.x] == '-') {
            game_status_ = OpenThisCell(cell.y, cell.x, cur_field_, field_, opened_cells_cnt_);
        }
        if (game_status_ == GameStatus::DEFEAT) {
            StopGame(false);
        }
    }
    if (mines_count_ + opened_cells_cnt_ == cur_field_.size() * cur_field_[0].size()) {
        StopGame(true);
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
    if (game_status_ == GameStatus::NOT_STARTED) {
        return 0;
    } else if (game_status_ == GameStatus::DEFEAT) {
        return time_;
    } else {
        return (time(nullptr) - time_);
    }
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    return cur_field_;
}
