#include "overflow_topology.h"

OverflowTopology::OverflowTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& [delta_x, delta_y] : shift_) {
        auto new_x = point.x + delta_x;
        auto new_y = point.y + delta_y;
        if (new_x < field_[0].size() && new_y < field_.size() && !field_[new_y][new_x]) {
            res.push_back({new_x, new_y});
        } else if (new_x >= Topology::UNREACHABLE && !field_[new_y][field_[0].size() - 1]) {
            res.push_back({field_[0].size() - 1, new_y});
        } else if (new_y >= Topology::UNREACHABLE && !field_[field_.size() - 1][new_x]) {
            res.push_back({new_x, field_.size() - 1});
        } else if (new_x >= field_[0].size() && !field_[new_y][0]) {
            res.push_back({0, new_y});
        } else if (new_y >= field_.size() && !field_[0][new_x]) {
            res.push_back({new_x, 0});
        }
    }

    return res;
}
