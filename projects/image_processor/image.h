#pragma once

#include "color.h"
#include <fstream>
#include <vector>

class Image {
public:
    size_t GetHeight() const;

    size_t GetWidth() const;

    size_t GetPadding() const;

    std::vector<std::vector<Color>> &GetPicture();

    void SetHeight(size_t new_height);

    void SetWidth(size_t new_width);

    void Load(std::ifstream &in);

    void Save(std::ofstream &out);

private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<Color>> picture_;
};
