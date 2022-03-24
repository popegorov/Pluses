#include "color.h"
#include <algorithm>

void Color::Clamp() {
    blue = std::clamp(blue, 0.0, 1.0);
    green = std::clamp(green, 0.0, 1.0);
    red = std::clamp(red, 0.0, 1.0);
}
