#include "password.h"

bool ValidatePassword(const std::string& password) {
    int pas_size = password.size();
    if (pas_size < 8 || pas_size > 14) {
        return false;
    }
    int big = 0;
    int small = 0;
    int digit = 0;
    int other = 0;
    for (int i = 0; i < pas_size; ++i) {
        char cur = password[i];
        if (cur < 33 || cur > 126) {
            return false;
        } else if (isdigit(cur)) {
            digit = 1;
        } else if (isupper(cur)) {
            big = 1;
        } else if (islower(cur)) {
            small = 1;
        } else {
            other = 1;
        }
    }
    if (digit + big + small + other < 3) {
        return false;
    }
    return true;
}