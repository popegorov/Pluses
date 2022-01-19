#include "password.h"

bool ValidatePassword(const std::string& password) {
    int pas_size = password.size();
    if (pas_size < 8 || pas_size > 14) {
        return false;
    }
    bool big = false;
    bool small = false;
    bool digit = false;
    bool other = false;
    for (int i = 0; i < pas_size; ++i) {
        char cur = password[i];
        if (cur < 33 || cur > 126) {
            return false;
        } else if (isdigit(cur)) {
            digit = true;
        } else if (isupper(cur)) {
            big = true;
        } else if (islower(cur)) {
            small = true;
        } else {
            other = true;
        }
    }
    return digit + big + small + other >= 3;
}