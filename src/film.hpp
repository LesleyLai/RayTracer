#ifndef FILM_HPP
#define FILM_HPP

#include <vector>

#include "color.hpp"

class Film
{
public:
    Film(size_t width, size_t height);

    void setResolution(size_t width, size_t height) noexcept;

    // Will write the color to (x, y) on the image
    void commit(size_t x, size_t y, const ColorRGB &color);

    /**
     * \brief Output image from buffer to a file.
     */
    void writeImage();

private:
    size_t width_;
    size_t height_;

    std::vector<ColorRGB> buffer_;
};

#endif // FILM_HPP
