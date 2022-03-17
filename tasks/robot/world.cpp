#include "world.h"

const Point& World::GetStart() const {
    return start_;
}

const Point& World::GetEnd() const {
    return end_;
}

const Point& World::GetCurrentPosition() const {
    return cur_position_;
}

World::World(const Topology& topology, Point start, Point end) {
    topology_ = &topology;
    start_ = start;
    cur_position_ = start;
    end_ = end;
}

std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> res;

    for (const auto& cur_neighbour : topology_->GetNeighbours(cur_position_)) {
        res[cur_neighbour] = topology_->MeasureDistance(cur_neighbour, end_);
    }

    return res;
}

void World::Move(const Point& to) {
    for (const auto& cur_neighbour : topology_->GetNeighbours(cur_position_)) {
        if (cur_neighbour == to) {
            cur_position_ = to;
        }
    }

    if (cur_position_ != to) {
        throw IllegalMoveException();
    }
}
