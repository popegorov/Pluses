#include "topology.h"
#include <queue>

const size_t INF = 1e9;

std::vector<Point> Topology::GetNeighbours(const Point& point) const {
    return std::vector<Point>();
}

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    auto height = field_.size();
    auto width = field_[0].size();

    std::vector<std::vector<size_t>> dist(height, std::vector<size_t>(width, INF));
    std::queue<Point> q;

    dist[from.y][from.x] = 0;
    q.push(from);

    while (!q.empty()) {
        auto cur_point = q.front();
        q.pop();

        for (const auto& [x, y] : GetNeighbours(cur_point)) {
            if (y < height && x < width && !field_[y][x] && dist[y][x] == INF) {
                dist[y][x] = dist[cur_point.y][cur_point.x] + 1;
                q.push({x, y});
            }
        }
    }
    if (dist[to.y][to.x] != INF) {
        return dist[to.y][to.x];
    }
    return UNREACHABLE;
}
