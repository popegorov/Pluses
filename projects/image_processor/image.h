#pragma once

#include "color.h"
#include <fstream>
#include <vector>

class Image {
public:
    using Picture = std::vector<std::vector<Color>>;

    Image() = default;
    Image(size_t width, size_t height);

    size_t GetHeight() const;

    size_t GetWidth() const;

    Picture GetPicture() const;

    Color& GetPixel(size_t x, size_t y);

    void Load(std::ifstream& in);

    void Save(std::ofstream& out);

private:
    Picture picture_;
};
