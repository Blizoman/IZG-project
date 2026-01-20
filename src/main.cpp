#include "framebuffer.h"
#include "graphics.h"
#include "ppm.h"
#include <iostream>
#include <cmath>

int main() {
    constexpr float PI = 3.14159265f;
    std::cout << "IZG Project - Computer Graphics Demo" << std::endl;
    
    // Create a framebuffer
    const int WIDTH = 800;
    const int HEIGHT = 600;
    Framebuffer fb(WIDTH, HEIGHT);
    
    // Clear with dark blue background
    fb.clear(Color(20, 20, 40));
    
    // Draw some shapes
    std::cout << "Drawing shapes..." << std::endl;
    
    // Draw a red circle
    Graphics::fillCircle(fb, 200, 200, 50, Colors::RED);
    
    // Draw a green rectangle
    Graphics::fillRectangle(fb, 300, 150, 400, 250, Colors::GREEN);
    
    // Draw a blue circle
    Graphics::fillCircle(fb, 600, 300, 80, Colors::BLUE);
    
    // Draw yellow triangles
    Graphics::drawTriangle(fb, 100, 400, 200, 500, 50, 550, Colors::YELLOW);
    Graphics::drawTriangle(fb, 500, 400, 600, 500, 550, 550, Colors::YELLOW);
    
    // Draw white lines
    Graphics::drawLine(fb, 0, 0, WIDTH - 1, HEIGHT - 1, Colors::WHITE);
    Graphics::drawLine(fb, WIDTH - 1, 0, 0, HEIGHT - 1, Colors::WHITE);
    
    // Draw some circles in a pattern
    for (int i = 0; i < 8; i++) {
        int x = 400 + static_cast<int>(150 * std::cos(i * PI / 4));
        int y = 400 + static_cast<int>(150 * std::sin(i * PI / 4));
        Graphics::drawCircle(fb, x, y, 20, Colors::CYAN);
    }
    
    // Draw a border
    Graphics::drawRectangle(fb, 0, 0, WIDTH - 1, HEIGHT - 1, Colors::MAGENTA);
    
    // Save to file
    std::cout << "Saving to output.ppm..." << std::endl;
    if (PPM::save("output.ppm", fb)) {
        std::cout << "Image saved successfully!" << std::endl;
        std::cout << "You can view it with an image viewer that supports PPM format." << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
        return 1;
    }
    
    return 0;
}
