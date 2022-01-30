#include "scorer.h"

bool EventCompare (const Event& first, const Event& second) {
    return first.time < second.time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<Event> new_events = events;
    std::sort(new_events.begin(), new_events.end(), EventCompare);
    std::map<std::pair<std::string, std::string>, std::pair<bool, bool>> student_scorer;
    for (const auto& [name, task, time, type] : new_events) {
        if (time > score_time) {
            break;
        } else if (type == EventType::CheckFailed) {
            student_scorer[std::make_pair(name, task)].first = true;
        } else if (type == EventType::CheckSuccess) {
            student_scorer[std::make_pair(name, task)].first = false;
        } else if (type == EventType::MergeRequestOpen) {
            student_scorer[std::make_pair(name, task)].second = true;
        } else {
            student_scorer[std::make_pair(name, task)].second = false;
        }
    }
    ScoreTable score_table;
    for (const auto& [name_task, check_merge] : student_scorer) {
        if (!check_merge.first && !check_merge.second) {
            score_table[name_task.first].insert(name_task.second);
        }
    }
    return score_table;
}
