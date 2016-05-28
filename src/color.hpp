#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>

enum class ColorType { RGB, RGBA };

/**
 * \brief color
 * \typedef ColorRGB
 */
template <typename T, ColorType type>
struct Color;

/**
 * \brief 24 bit float RGB color
 */
template <>
struct Color<float, ColorType::RGB> {
    /// Red component of the color.
    float r;

    /// Green component of the color.
    float g;

    /// Blue component of the color.
    float b;

    /**
     * \brief Constructs a new black 24 bit RGB Color.
     */
    constexpr Color() :
        r{0},
        g{0},
        b{0}
    {}

    /**
     * \brief Constructs a new 24 bit float RGB Color with given r,g,b components.
     * \param red, green, blue
     */
    constexpr Color(float red, float green, float blue) :
        r{red},
        g{green},
        b{blue} {
    }

    void operator+=(const Color &rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        clampcolor();
    }

    void operator-=(const Color &rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        clampcolor();
    }

    constexpr bool operator==(const Color &rhs) {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    constexpr Color operator+(const Color &rhs) const {
        return Color(r+rhs.r, g+rhs.g, b+rhs.b);
    }

    constexpr Color operator-(const Color &rhs) const {
        return Color(r-rhs.r, g-rhs.g, b-rhs.b);
    }

    constexpr Color operator*(const Color &rhs) const {
        return Color(r*rhs.r, g*rhs.g, b*rhs.b);
    }

    constexpr Color operator*(const float scalar) const {
        return Color(r*scalar, g*scalar, b*scalar);
    }

    /**
     * \brief Operator << of ColorRGB.
     * @tparam CharT  Type of character stream.
     * @tparam Traits  Traits for character type.
     * \param os The output stream
     * \param vec The vector to be output.
     */
    template <class CharT, class Traits>
    inline friend std::basic_ostream<CharT, Traits>&
        operator<<(std::basic_ostream<CharT, Traits>& os,
                   const Color& color) {
        os << "Color(" << color.r << "," << color.g  << "," << color.b << ")";
        return os;
    }

private:
    void clampcolor() {
        r = std::max(r , 0.0f);
        r = std::min(r , 1.0f);
        g = std::max(g , 0.0f);
        g = std::min(g , 1.0f);
        b = std::max(b , 0.0f);
        b = std::min(b , 1.0f);
    }

};

using ColorRGB = Color<float, ColorType::RGB>;


#endif // COLOR_HPP
