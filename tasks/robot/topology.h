#pragma once

#include "point.h"

#include <vector>

class Topology {
public:
    using Distance = ssize_t;

    virtual std::vector<Point> GetNeighbours(const Point& point) const;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    static const Distance UNREACHABLE;

protected:
    std::vector<std::vector<bool>> field_;
};
