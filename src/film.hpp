#ifndef FILM_HPP
#define FILM_HPP

#include <vector>

#include "color.hpp"

class Film
{
public:
    Film(int width, int height);

    void setResolution(int width, int height) noexcept;

    // Will write the color to (x, y) on the image
    void commit(int x, int y, const ColorRGB &color);

    /**
     * \brief Output image from buffer to a file.
     */
    void writeImage();

private:
    int width_;
    int height_;

    std::vector<ColorRGB> buffer_;
};

#endif // FILM_HPP
