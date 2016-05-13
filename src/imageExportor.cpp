#include <stdexcept>
#include <iostream>

#include "FreeImage.h"

#include "imageExportor.hpp"

constexpr int BIT_PER_PIXEL = 24;

ImageExportor::ImageExportor() {

}

void ImageExportor::exportImage(int width, int height, std::vector<ColorRGB> &buffer) {
    FreeImage_Initialise();

    FIBITMAP *bitmap = FreeImage_Allocate(width, height, BIT_PER_PIXEL);
    if (!bitmap) throw std::runtime_error("Cannot allocate image");

    RGBQUAD color;
    for (int x = 0; x != width; ++x) {
        for (int y = 0; y != height; ++y) {
            int index = x + y  * width;
            color.rgbRed = buffer[index].r * 255;
            color.rgbGreen = buffer[index].g * 255;
            color.rgbBlue = buffer[index].b * 255;
            FreeImage_SetPixelColor(bitmap, x, y, &color);
        }
    }

    std::string filename = "testimage.png";

    if (FreeImage_Save(FIF_PNG, bitmap, filename.c_str(), 0)) {
        std::cout << "Successfully saved image \"" << filename << "\"" << std::endl;
    } else {
        throw std::runtime_error("Cannot saved image \"" + filename + "\"");
    }

    FreeImage_DeInitialise();
}
