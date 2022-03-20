#include "image_processor.h"

void ImageProcessor::Load(std::ifstream& in) {
    im_.Load(in);
}

void ImageProcessor::Save(std::ofstream& out) {
    im_.Save(out);
}

void ImageProcessor::FilterCrop(size_t width, size_t height) {
    Crop c(width, height);
    c.Modify(im_);
}

void ImageProcessor::FilterGs() {
    Gs g;
    g.Modify(im_);
}

void ImageProcessor::FilterNeg() {
    Neg n;
    n.Modify(im_);
}