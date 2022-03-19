#include "checkers_topology.h"
#include <queue>

CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& [delta_x, delta_y] : shift_) {
        auto new_x = point.x + delta_x;
        auto new_y = point.y + delta_y;
        if (new_x < field_[0].size() && new_y < field_.size() && !field_[new_y][new_x]) {
            res.push_back({new_x, new_y});
        }
    }

    std::queue<Point> q;
    std::vector<std::vector<bool>> visited(field_.size(), std::vector<bool>(field_[0].size()));
    q.push(point);
    visited[point.y][point.x] = true;

    while (!q.empty()) {
        auto cur_point = q.front();
        q.pop();
        for (const auto& [delta_x, delta_y] : shift_) {
            auto new_x = cur_point.x + delta_x;
            auto new_y = cur_point.y + delta_y;
            auto after_new_x = cur_point.x + 2 * delta_x;
            auto after_new_y = cur_point.y + 2 * delta_y;

            if (after_new_x < field_[0].size() && after_new_y < field_.size() && field_[new_y][new_x] &&
                !field_[after_new_y][after_new_x] && !visited[after_new_y][after_new_x]) {

                q.push({after_new_x, after_new_y});
                visited[after_new_y][after_new_x] = true;
                res.push_back({after_new_x, after_new_y});
            }
        }
    }

    return res;
}
