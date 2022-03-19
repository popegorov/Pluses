#pragma once

#include "topology.h"

class OverflowTopology : public Topology {
public:
    OverflowTopology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetNeighbours(const Point& point) const override;

private:
    std::vector<std::pair<int, int>> shift_ = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};
