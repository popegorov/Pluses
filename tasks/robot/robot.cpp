#include "robot.h"

robot::Path robot::FindPath(World& world) {
    robot::Path res = {world.GetStart()};
    size_t min_dist = Topology::UNREACHABLE;
    Point min_neighbour;

    while (world.GetCurrentPosition() != world.GetEnd()) {
        for (const auto& [neighbour, cur_dist] : world.Lookup()) {
            if (cur_dist < min_dist && cur_dist != Topology::UNREACHABLE) {
                min_dist = cur_dist;
                min_neighbour = neighbour;
            }
        }

        if (min_dist == Topology::UNREACHABLE) {
            return robot::Path();
        }
        min_dist = Topology::UNREACHABLE;
        res.push_back(min_neighbour);
        world.Move(min_neighbour);
    }
    return res;
}