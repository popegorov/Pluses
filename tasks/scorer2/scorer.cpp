#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    checked_[student_name].erase(task_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    checked_[student_name].insert(task_name);
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    request_opened_[student_name].insert(task_name);
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    request_opened_[student_name].erase(task_name);
}

void Scorer::Reset() {
    checked_.clear();
    request_opened_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable result;
    for (const auto& [student_name, tasks] : checked_) {
        for (const auto& task : tasks) {
            if (!request_opened_.contains(student_name) || (request_opened_.contains(student_name) && !request_opened_.at(student_name).contains(task))) {
                result[student_name].insert(task);
            }
        }
    }
    return result;
}
