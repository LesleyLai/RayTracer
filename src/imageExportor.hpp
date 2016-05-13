#ifndef IMAGEEXPORTOR_HPP
#define IMAGEEXPORTOR_HPP

#include <vector>

#include "color.hpp"

class ImageExportor
{
public:
    ImageExportor();

    void exportImage(int width, int height, std::vector<ColorRGB> &buffer);
};

#endif // IMAGEEXPORTOR_HPP
