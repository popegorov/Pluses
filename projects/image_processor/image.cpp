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

uint8_t ReadByte(std::ifstream& input) {
    uint8_t byte;
    input.read(reinterpret_cast<char*>(&byte), 1);
    return byte;
}

void SkipNBytes(std::ifstream& input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        ReadByte(input);
    }
}

uint32_t ReadInt(std::ifstream& input) {
    auto a = ReadByte(input);
    auto b = ReadByte(input);
    auto c = ReadByte(input);
    auto d = ReadByte(input);

    return a + (b << 8) + (c << 16) + (d << 24);
}

Color ReadColor(std::ifstream& input) {
    double blue = MakeDouble(ReadByte(input));
    double green = MakeDouble(ReadByte(input));
    double red = MakeDouble(ReadByte(input));
    return {red, green, blue};
}

void WriteByte(std::ofstream& output, uint8_t byte) {
    output.write(reinterpret_cast<char *>(&byte), 1);
}

void WriteInt(std::ofstream& output, uint32_t value) {
    WriteByte(output, value % (1 << 8));
    WriteByte(output, (value / (1 << 8)) % (1 << 8));
    WriteByte(output, (value / (1 << 16)) % (1 << 8));
    WriteByte(output, value / (1 << 24));
}

void WriteColor(std::ofstream& out, const Color& color) {
    WriteByte(out, MakeUint8_t(color.blue));
    WriteByte(out, MakeUint8_t(color.green));
    WriteByte(out, MakeUint8_t(color.red));
}

void WriteNBytes(std::ofstream& out, size_t n, uint8_t value = 0) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(out, value);
    }
}

void SaveStandardInformation(std::ofstream& out, size_t width, size_t height) {
    auto padding = CalculatePadding(width);
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

    WriteNBytes(out, 16);
}

} // namespace

Image::Image(size_t width, size_t height) {
    picture_ = Picture(height, std::vector<Color>(width));
}

size_t Image::GetHeight() const {
    return picture_.size();
}

size_t Image::GetWidth() const {
    if (!picture_.empty()) {
        return picture_[0].size();
    }
    return 0;
}

std::vector<std::vector<Color>> Image::GetPicture() const {
    return picture_;
}

Color& Image::GetPixel(size_t x, size_t y) {
    return picture_[y][x];
}

void Image::Load(std::ifstream& in) {
    SkipNBytes(in, 18);
    size_t width = ReadInt(in);
    size_t height = ReadInt(in);
    SkipNBytes(in, 28);

    picture_.assign(height, std::vector<Color>(width));
    auto padding = CalculatePadding(GetWidth());
    for (size_t y = GetHeight(); y > 0; --y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            GetPixel(x, y - 1) = ReadColor(in);
        }
        SkipNBytes(in, padding);
    }

}

void Image::Save(std::ofstream& out) {
    SaveStandardInformation(out, GetWidth(), GetHeight());

    auto padding = CalculatePadding(GetWidth());
    for (size_t y = GetHeight(); y > 0; --y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            WriteColor(out, GetPixel(x, y - 1));
        }
        WriteNBytes(out, padding);
    }
}
