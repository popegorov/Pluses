#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].first = true;
    if (result_.contains(student_name) && result_[student_name].contains(task_name)) {
        result_[student_name].erase(task_name);
        if (result_[student_name].empty()) {
            result_.erase(student_name);
        }
    }
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].first = false;
    if (!current_results_[{student_name, task_name}].second) {
        result_[student_name].insert(task_name);
        current_results_.erase({student_name, task_name});
    }
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].second = true;
    if (result_.contains(student_name) && result_[student_name].contains(task_name)) {
        result_[student_name].erase(task_name);
    }
    if (result_[student_name].empty()) {
        result_.erase(student_name);
    }
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    current_results_[{student_name, task_name}].second = false;
    if (!current_results_[{student_name, task_name}].first) {
        result_[student_name].insert(task_name);
        current_results_.erase({student_name, task_name});
    }
}

void Scorer::Reset() {
    current_results_.clear();
    result_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return result_;
}