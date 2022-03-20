#include "image.h"

namespace {

size_t CalculatePadding(size_t width) {
    return (4 - (width * 3) % 4) % 4;
}

uint8_t MakeUint8_t(double x) {
    return x * 255;
}

double MakeDouble(uint8_t x) {
    return static_cast<double>(x) / 255;
}

uint8_t ReadByte(std::ifstream &input) {
    uint8_t byte;
    input.read(reinterpret_cast<char *>(&byte), 1);
    return byte;
}

void SkipNBytes(std::ifstream &input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        ReadByte(input);
    }
}

uint32_t ReadInt(std::ifstream &input) {
    auto a = ReadByte(input);
    auto b = ReadByte(input);
    auto c = ReadByte(input);
    auto d = ReadByte(input);

    return a + (b << 8) + (c << 16) + (d << 24);
}

void ReadColor(std::ifstream& in, Image& im, size_t x, size_t y) {
    im.GetPicture()[y][x].blue = MakeDouble(ReadByte(in));
    im.GetPicture()[y][x].green = MakeDouble(ReadByte(in));
    im.GetPicture()[y][x].red = MakeDouble(ReadByte(in));
}

void WriteByte(std::ofstream &output, uint8_t byte) {
    output.write(reinterpret_cast<char *>(&byte), 1);
}

void WriteInt(std::ofstream &output, uint32_t value) {
    WriteByte(output, value % (1 << 8));
    WriteByte(output, (value / (1 << 8)) % (1 << 8));
    WriteByte(output, (value / (1 << 16)) % (1 << 8));
    WriteByte(output, value / (1 << 24));
}

void WriteColor(std::ofstream& out, Image& im, size_t x, size_t y) {
    WriteByte(out, MakeUint8_t(im.GetPicture()[y][x].blue));
    WriteByte(out, MakeUint8_t(im.GetPicture()[y][x].green * 255));
    WriteByte(out, MakeUint8_t(im.GetPicture()[y][x].red * 255));
}

void WriteNBytes(std::ofstream& out, size_t n, uint8_t value = 0) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(out, value);
    }
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
    return CalculatePadding(width_);
}

std::vector<std::vector<Color>> &Image::GetPicture() {
    return picture_;
}

void Image::Load(std::ifstream &in) {
    SkipNBytes(in, 18);
    width_ = ReadInt(in);
    height_ = ReadInt(in);
    SkipNBytes(in, 28);

    GetPicture().assign(GetHeight(), std::vector<Color>(GetWidth()));
    for (size_t y = GetHeight(); y > 0; --y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            ReadColor(in, *this, x, y - 1);
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
            WriteColor(out, *this, x, y - 1);
        }
        WriteNBytes(out, GetPadding());
    }
}