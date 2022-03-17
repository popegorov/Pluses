#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    KnightTopology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetNeighbours(const Point& point) const override;

private:
    std::vector<std::pair<int, int>> shift_ = {{-1, 2}, {1, 2}, {2, -1}, {2, 1}, {-1, -2}, {1, -2}, {-2, -1}, {-2, 1}};
};
