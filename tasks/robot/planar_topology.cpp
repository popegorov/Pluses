#include "planar_topology.h"
#include <world.h>

PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& field) {
    field_ = field;
}

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> res;

    for (const auto& [delta_x, delta_y] : shift_) {
        auto new_x = point.x + delta_x;
        auto new_y = point.y + delta_y;
        if (new_x < field_[0].size() && new_y < field_.size() && !field_[new_y][new_x]) {
            res.push_back({new_x, new_y});
        }
    }

    return res;
}
