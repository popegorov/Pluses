#pragma once

#include <fstream>
#include <vector>

struct Color {
    double red;
    double green;
    double blue;
};

class Image {
public:
    size_t GetHeight() const;

    size_t GetWidth() const;

    size_t GetPadding() const;

    std::vector<std::vector<Color>> &GetPicture();

    void SetHeight(size_t new_height);

    void SetWidth(size_t new_width);

    void SetPadding(size_t new_width);

    void Load(std::ifstream &in);

    void Save(std::ofstream &out);

private:
    size_t height_;
    size_t width_;
    size_t padding_;
    std::vector<std::vector<Color>> picture_;
    size_t size_of_the_raw_bitmap_data_;
};
