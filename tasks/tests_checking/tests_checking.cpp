#include "tests_checking.h"
#include <deque>
#include <vector>


std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> tests;
    for (const auto& student : student_actions) {
        if (student.side == Side::Bottom){
            tests.push_back(student.name);
        } else {
            tests.push_front(student.name);
        }
    }

    std::vector<std::string> student_check;

    for (const auto& test_number : queries) {
        student_check.push_back(tests[test_number - 1]);
    }
    return student_check;
}
