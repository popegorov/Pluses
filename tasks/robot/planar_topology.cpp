#include "planar_topology.h"
#include <world.h>

PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& cur_shift : shift_) {
        if ((point.x + cur_shift.first) < field_[0].size() && (point.y + cur_shift.second) < field_.size() &&
            !field_[point.y + cur_shift.second][point.x + cur_shift.first]) {
            res.push_back({point.x + cur_shift.first, point.y + cur_shift.second});
        }
    }

    return res;
}
