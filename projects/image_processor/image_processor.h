#pragma once

#include "image.h"
#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"

class ImageProcessor {
public:
    void Load(std::ifstream& in);
    void Save(std::ofstream& out);
    void FilterCrop(size_t width, size_t height);
    void FilterGs();
    void FilterNeg();
private:
    Image im_;
};



