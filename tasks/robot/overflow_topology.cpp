#include "overflow_topology.h"

const size_t INF = 1e9;

OverflowTopology::OverflowTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& cur_shift : shift_) {
        if ((point.x + cur_shift.first) < field_[0].size() && (point.y + cur_shift.second) < field_.size() &&
            !field_[point.y + cur_shift.second][point.x + cur_shift.first]) {
            res.push_back({point.x + cur_shift.first, point.y + cur_shift.second});
        } else if ((point.x + cur_shift.first) > INF && !field_[point.y + cur_shift.second][field_[0].size() - 1]) {
            res.push_back({field_[0].size() - 1, point.y + cur_shift.second});
        } else if (point.y + cur_shift.second > INF && !field_[field_.size() - 1][point.x + cur_shift.first]) {
            res.push_back({point.x + cur_shift.first, field_.size() - 1});
        }
    }

    return res;
}
