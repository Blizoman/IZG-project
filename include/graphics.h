#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "framebuffer.h"
#include "vector.h"
#include <algorithm>

/**
 * @brief Graphics primitives for 2D rendering
 */
class Graphics {
public:
    /**
     * @brief Draw a line using Bresenham's algorithm
     */
    static void drawLine(Framebuffer& fb, int x0, int y0, int x1, int y1, const Color& color) {
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;
        
        while (true) {
            fb.setPixel(x0, y0, color);
            
            if (x0 == x1 && y0 == y1) break;
            
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
    
    /**
     * @brief Draw a circle using midpoint circle algorithm
     */
    static void drawCircle(Framebuffer& fb, int cx, int cy, int radius, const Color& color) {
        int x = radius;
        int y = 0;
        int err = 0;
        
        while (x >= y) {
            fb.setPixel(cx + x, cy + y, color);
            fb.setPixel(cx + y, cy + x, color);
            fb.setPixel(cx - y, cy + x, color);
            fb.setPixel(cx - x, cy + y, color);
            fb.setPixel(cx - x, cy - y, color);
            fb.setPixel(cx - y, cy - x, color);
            fb.setPixel(cx + y, cy - x, color);
            fb.setPixel(cx + x, cy - y, color);
            
            if (err <= 0) {
                y++;
                err += 2 * y + 1;
            }
            if (err > 0) {
                x--;
                err -= 2 * x + 1;
            }
        }
    }
    
    /**
     * @brief Fill a circle
     */
    static void fillCircle(Framebuffer& fb, int cx, int cy, int radius, const Color& color) {
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    fb.setPixel(cx + x, cy + y, color);
                }
            }
        }
    }
    
    /**
     * @brief Draw a rectangle
     */
    static void drawRectangle(Framebuffer& fb, int x0, int y0, int x1, int y1, const Color& color) {
        drawLine(fb, x0, y0, x1, y0, color);
        drawLine(fb, x1, y0, x1, y1, color);
        drawLine(fb, x1, y1, x0, y1, color);
        drawLine(fb, x0, y1, x0, y0, color);
    }
    
    /**
     * @brief Fill a rectangle
     */
    static void fillRectangle(Framebuffer& fb, int x0, int y0, int x1, int y1, const Color& color) {
        int minX = std::min(x0, x1);
        int maxX = std::max(x0, x1);
        int minY = std::min(y0, y1);
        int maxY = std::max(y0, y1);
        
        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                fb.setPixel(x, y, color);
            }
        }
    }
    
    /**
     * @brief Draw a triangle
     */
    static void drawTriangle(Framebuffer& fb, int x0, int y0, int x1, int y1, int x2, int y2, const Color& color) {
        drawLine(fb, x0, y0, x1, y1, color);
        drawLine(fb, x1, y1, x2, y2, color);
        drawLine(fb, x2, y2, x0, y0, color);
    }
};

#endif // GRAPHICS_H
