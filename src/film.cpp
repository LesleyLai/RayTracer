#include <stdexcept>
#include <sstream>

#include "film.hpp"

#include "imageExportor.hpp"

Film::Film(int width, int height) :
    width_{width},
    height_{height},
    buffer_{static_cast<std::size_t>(width) * height} {
}

void Film::setResolution(int width, int height) noexcept {
    width_ = width;
    height_ = height;
    buffer_.resize(width_ * height_);
}

void Film::commit(int x, int y, const ColorRGB &color) {
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
