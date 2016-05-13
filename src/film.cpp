#include "film.hpp"

#include "imageExportor.hpp"

Film::Film(int width, int height) : width_{width}, height_{height} {

}

void Film::setResolution(int width, int height) {
    width_ = width;
    height_ = height;
}

void Film::writeImage() {
    ImageExportor imageExportor;
    imageExportor.exportImage(width_, height_);
}
