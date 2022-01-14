#include "password.h"

bool ValidatePassword(const std::string& password) {
    int pas_size = password.size();
    bool flag = true;
    if (pas_size < 8 || pas_size > 14) {
        flag = false;
    }
    int big = 0;
    int small = 0;
    int digit = 0;
    int other = 0;
    for (int i = 0; i < pas_size; ++i) {
        char cur = password[i];
        if (cur + 0 < 33 || cur + 0 > 126) {
            flag = false;
        } else if (cur + 0 >= 48 && cur + 0 <= 57) {
            digit = 1;
        } else if (cur + 0 >= 65 && cur + 0 <= 90) {
            big = 1;
        } else if (cur + 0 >= 97 && cur + 0 <= 122) {
            small = 1;
        } else {
            other = 1;
        }
    }
    if (digit + big + small + other < 3) {
        flag = false;
    }
    return flag;
}
