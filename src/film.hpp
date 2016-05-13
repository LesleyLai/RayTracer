#ifndef FILM_HPP
#define FILM_HPP


class Film
{
public:
    Film(int width, int height);

    void setResolution(int width, int height);

    // Output image to a file
    void writeImage();

private:
    int width_;
    int height_;
};

#endif // FILM_HPP
