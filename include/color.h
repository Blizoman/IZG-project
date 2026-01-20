#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

/**
 * @brief RGB Color structure
 */
struct Color {
    unsigned char r, g, b;
    
    Color() : r(0), g(0), b(0) {}
    Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
    
    /**
     * @brief Create color from float values (0.0 - 1.0)
     */
    static Color fromFloat(float r, float g, float b) {
        return Color(
            static_cast<unsigned char>(std::clamp(r, 0.0f, 1.0f) * 255),
            static_cast<unsigned char>(std::clamp(g, 0.0f, 1.0f) * 255),
            static_cast<unsigned char>(std::clamp(b, 0.0f, 1.0f) * 255)
        );
    }
    
    /**
     * @brief Linearly interpolate between two colors
     */
    static Color lerp(const Color& c1, const Color& c2, float t) {
        t = std::clamp(t, 0.0f, 1.0f);
        return Color(
            static_cast<unsigned char>(c1.r + (c2.r - c1.r) * t),
            static_cast<unsigned char>(c1.g + (c2.g - c1.g) * t),
            static_cast<unsigned char>(c1.b + (c2.b - c1.b) * t)
        );
    }
};

// Common colors
namespace Colors {
    const Color BLACK(0, 0, 0);
    const Color WHITE(255, 255, 255);
    const Color RED(255, 0, 0);
    const Color GREEN(0, 255, 0);
    const Color BLUE(0, 0, 255);
    const Color YELLOW(255, 255, 0);
    const Color CYAN(0, 255, 255);
    const Color MAGENTA(255, 0, 255);
}

#endif // COLOR_H
