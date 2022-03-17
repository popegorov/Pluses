#include "checkers_topology.h"
#include <queue>

CheckersTopology::CheckersTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& cur_shift : shift_) {
        if ((point.x + cur_shift.first) < field_[0].size() && (point.y + cur_shift.second) < field_.size() &&
            !field_[point.y + cur_shift.second][point.x + cur_shift.first]) {
            res.push_back({point.x + cur_shift.first, point.y + cur_shift.second});
        }
    }

    std::queue<Point> q;
    std::vector<std::vector<bool>> visited(field_.size(), std::vector<bool>(field_[0].size()));
    q.push(point);
    visited[point.y][point.x] = true;

    while (!q.empty()) {
        auto cur_point = q.front();
        q.pop();
        for (const auto& cur_shift : shift_) {
            if ((cur_point.x + 2 * cur_shift.first) < field_[0].size() &&
                (cur_point.y + 2 * cur_shift.second) < field_.size() &&
                field_[cur_point.y + cur_shift.second][cur_point.x + cur_shift.first] &&
                !field_[cur_point.y + 2 * cur_shift.second][cur_point.x + 2 * cur_shift.first] &&
                !visited[cur_point.y + 2 * cur_shift.second][cur_point.x + 2 * cur_shift.first]) {

                q.push({cur_point.x + 2 * cur_shift.first, cur_point.y + 2 * cur_shift.second});
                visited[cur_point.y + 2 * cur_shift.second][cur_point.x + 2 * cur_shift.first] = true;
                res.push_back({cur_point.x + 2 * cur_shift.first, cur_point.y + 2 * cur_shift.second});
            }
        }
    }

    return res;
}
