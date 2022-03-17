#include "robot.h"

const size_t INF = 1e9;

robot::Path robot::FindPath(World& world) {
    robot::Path res = {world.GetStart()};
    size_t min_dist = INF;
    Point min_neighbour;

    while (world.GetCurrentPosition() != world.GetEnd()) {
        auto lookup = world.Lookup();
        for (const auto& [neighbour, cur_dist] : lookup) {
            if (cur_dist < min_dist && cur_dist != Topology::UNREACHABLE) {
                min_dist = cur_dist;
                min_neighbour = neighbour;
            }
        }

        if (min_dist == INF) {
            return robot::Path();
        }
        min_dist = INF;
        res.push_back(min_neighbour);
        world.Move(min_neighbour);
    }
    return res;
}