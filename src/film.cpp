#include <stdexcept>
#include <sstream>

#include "film.hpp"

#include "imageExportor.hpp"

Film::Film(size_t width, size_t height) :
    width_{width},
    height_{height},
    buffer_{width * height} {
}

void Film::setResolution(size_t width, size_t height) noexcept {
    width_ = width;
    height_ = height;
    buffer_.resize(width_ * height_);
}

void Film::commit(size_t x, size_t y, const ColorRGB &color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        std::stringstream ss;
        ss << "Cannot commit color to pixel ("
           << x << "," << y
           << ") since the resolution of the film is ("
           << width_ << "x" << height_ << ").";
        throw std::out_of_range(ss.str());
    }

    buffer_[x + y  * width_] = color;
}

void Film::writeImage() {
    ImageExportor imageExportor;
    imageExportor.exportImage(width_, height_, buffer_);
}
