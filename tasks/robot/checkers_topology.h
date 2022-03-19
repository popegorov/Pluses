#pragma once

#include "topology.h"

class CheckersTopology : public Topology {
public:
    CheckersTopology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetNeighbours(const Point& point) const override;

private:
    std::vector<std::pair<int, int>> shift_ = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
};
