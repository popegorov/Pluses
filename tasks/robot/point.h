#pragma once

#include <cstddef>
#include <functional>

struct Point {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Point& other) const;
};

template<>
struct std::hash<Point> {
    size_t operator()(const Point& a) const  {
        return a.x * 809 + a.y * 907;
    }
};
