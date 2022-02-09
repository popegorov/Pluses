#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].first = true;
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].first = false;
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].second = true;
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].second = false;
}

void Scorer::Reset() {
    current_results_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable result;
    for (const auto& [name_task, check_merge] : current_results_) {
        if (!check_merge.first && !check_merge.second) {
            result[name_task.first].insert(name_task.second);
        }
    }
    return result;
}