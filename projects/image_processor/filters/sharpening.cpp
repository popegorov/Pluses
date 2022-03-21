#include "sharpening.h"
#include "matrix.h"

void Sharpening::Modify(Image &im) {
    Image::Picture picture_copy(im.GetPicture());

    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            matrix::SubtractAllNeighbours(im, picture_copy, x, y);
            matrix::ChangeColor(im, picture_copy, x, y, x, y, 4);
            matrix::CheckPixel(im.GetPixel(x, y));
        }
    }
}
