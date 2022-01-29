#include "admission.h"
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

bool DatesAreEqual(const Date& first, const Date& second) {
    return first.year == second.year && first.month == second.month && first.day == second.day;
}

bool CompareDate(const Date& first, const Date& second) {
    if (first.year != second.year) {
        return first.year < second.year;
    } else if (first.month != second.month) {
        return first.month < second.month;
    } else {
        return first.day < second.day;
    }
}

bool CompareApplicants(const Applicant& first, const Applicant& second) {
    if (first.points != second.points) {
        return first.points > second.points;
    } else if (!DatesAreEqual(first.student.birth_date, second.student.birth_date)) {
        return CompareDate(first.student.birth_date, second.student.birth_date);
    } else {
        return first.student.name < second.student.name;
    }
}

bool CompareStudents(const Student*& first, const Student*& second) {
    return std::tie(first->name, first->birth_date.year, first->birth_date.month, first->birth_date.day) <
           std::tie(second->name, second->birth_date.year, second->birth_date.month, second->birth_date.day);
}

std::unordered_map<std::string, int> GeneratingUniversityTable(const std::vector<University>& universities) {
    std::unordered_map<std::string, int> university_table;
    for (size_t i = 0; i < universities.size(); ++i) {
        university_table[universities[i].name] = universities[i].max_students;
    }
    return university_table;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<Applicant> sorted_applicants = applicants;
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), CompareApplicants);
    AdmissionTable admission;
    std::unordered_map<std::string, int> university_table = GeneratingUniversityTable(universities);
    for (size_t i = 0; i < applicants.size(); ++i) {
        for (size_t j = 0; j < applicants[i].wish_list.size(); ++j) {
            if (university_table[applicants[i].wish_list[j]] > admission[applicants[i].wish_list[j]].size()) {
                admission[applicants[i].wish_list[j]].push_back(&applicants[i].student);
                break;
            }
        }
    }
    for (auto& [university, student_list] : admission) {
        std::sort(student_list.begin(), student_list.end(), CompareStudents);
    }
    return admission;
}
