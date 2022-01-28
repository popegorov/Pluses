#include "tests_checking.h"
#include <deque>


std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> tests;
    std::vector<std::string> student_check(queries.size());
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Bottom){
            tests.push_back(student_actions[i].name);
        } else {
            tests.push_front(student_actions[i].name);
        }
    }
    for (size_t i = 0; i < queries.size(); ++i) {
        student_check[i] = tests[queries[i] - 1];
    }
    return student_check;
}
