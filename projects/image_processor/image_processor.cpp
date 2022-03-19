#include "image_processor.h"


namespace {

void WriteByte(std::ofstream &output, uint8_t byte) {
    output.write(reinterpret_cast<char *>(&byte), 1);
}

uint8_t ReadByte(std::ifstream &input) {
    uint8_t byte;
    input.read(reinterpret_cast<char *>(&byte), 1);
    return byte;
}

void CopyNBytes(std::ifstream &input, std::ofstream &output, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(output, ReadByte(input));
    }
}

uint32_t ReadInt(std::ifstream &input) {
    auto a = ReadByte(input);
    auto b = ReadByte(input);
    auto c = ReadByte(input);
    auto d = ReadByte(input);

    return a + (b << 8) + (c << 16) + (d << 24);
}

void WriteInt(std::ofstream &output, uint32_t value) {
    WriteByte(output, value % (1 << 8));
    WriteByte(output, (value / (1 << 8)) % (1 << 8));
    WriteByte(output, (value / (1 << 16)) % (1 << 8));
    WriteByte(output, value / (1 << 24));
}


void SkipNBytes(std::ifstream &input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        ReadByte(input);
    }
}

size_t CalculatePadding(size_t width) {
    return (4 - (width * 3) % 4) % 4;
}

} // namespace

size_t Image::GetHeight() const {
    return height_;
}

void Image::SetHeight(size_t new_height) {
    height_ = new_height;
}

size_t Image::GetWidth() const {
    return width_;
}

void Image::SetWidth(size_t new_width) {
    width_ = new_width;
}

size_t Image::GetPadding() const {
    return padding_;
}

void Image::SetPadding(size_t new_width) {
    padding_ = CalculatePadding(new_width);
}

std::vector<std::vector<Color>> &Image::GetPicture() {
    return picture_;
}

void Image::Load(std::ifstream &in) {
    SkipNBytes(in, 18);
    width_ = ReadInt(in);
    height_ = ReadInt(in);
    SkipNBytes(in, 8);
    size_of_the_raw_bitmap_data_ = ReadInt(in);
    SkipNBytes(in, 16);

    padding_ = CalculatePadding(GetWidth());
    GetPicture().assign(GetHeight(), std::vector<Color>(GetWidth()));
    for (size_t y = GetHeight(); y > 0; --y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            GetPicture()[y - 1][x].blue = static_cast<double>(ReadByte(in)) / 255;
            GetPicture()[y - 1][x].green = static_cast<double>(ReadByte(in)) / 255;
            GetPicture()[y - 1][x].red = static_cast<double>(ReadByte(in)) / 255;
        }
        SkipNBytes(in, GetPadding());
    }
}

void SaveStandardInformation(std::ofstream &out, size_t width, size_t height, size_t padding) {
    WriteByte(out, 66);
    WriteByte(out, 77);

    WriteInt(out, 54 + (width * 3 + padding) * height);

    WriteInt(out, 0);

    WriteInt(out, 54);

    WriteInt(out, 40);

    WriteInt(out, width);

    WriteInt(out, height);

    WriteByte(out, 1);
    WriteByte(out, 0);

    WriteByte(out, 24);
    WriteByte(out, 0);

    WriteInt(out, 0);
    WriteInt(out, (width * 3 + padding) * height);
    WriteInt(out, 0);
    WriteInt(out, 0);
    WriteInt(out, 0);
    WriteInt(out, 0);
}

void Image::Save(std::ofstream &out) {
    SaveStandardInformation(out, GetWidth(), GetHeight(), GetPadding());

    for (size_t y = GetHeight(); y >= 1; --y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            WriteByte(out, GetPicture()[y - 1][x].blue * 255);
            WriteByte(out, GetPicture()[y - 1][x].green * 255);
            WriteByte(out, GetPicture()[y - 1][x].red * 255);
        }
        for (size_t i = 0; i < GetPadding(); ++i) {
            WriteByte(out, 0);
        }
    }
}
