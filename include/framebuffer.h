#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "color.h"
#include <vector>

/**
 * @brief Simple framebuffer for rendering
 */
class Framebuffer {
private:
    int width;
    int height;
    std::vector<Color> pixels;
    
public:
    Framebuffer(int w, int h) : width(w), height(h), pixels(w * h, Colors::BLACK) {}
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    /**
     * @brief Set pixel color at (x, y)
     */
    void setPixel(int x, int y, const Color& color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color;
        }
    }
    
    /**
     * @brief Get pixel color at (x, y)
     */
    Color getPixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y * width + x];
        }
        return Colors::BLACK;
    }
    
    /**
     * @brief Clear framebuffer with color
     */
    void clear(const Color& color = Colors::BLACK) {
        std::fill(pixels.begin(), pixels.end(), color);
    }
    
    /**
     * @brief Get raw pixel data
     */
    const Color* getData() const {
        return pixels.data();
    }
};

#endif // FRAMEBUFFER_H
