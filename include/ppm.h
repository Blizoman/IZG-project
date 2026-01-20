#ifndef PPM_H
#define PPM_H

#include "framebuffer.h"
#include <fstream>
#include <string>

/**
 * @brief PPM image file writer
 */
class PPM {
public:
    /**
     * @brief Save framebuffer to PPM file
     */
    static bool save(const std::string& filename, const Framebuffer& fb) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // Write PPM header
        file << "P6\n" << fb.getWidth() << " " << fb.getHeight() << "\n255\n";
        
        // Write pixel data
        const Color* data = fb.getData();
        for (int i = 0; i < fb.getWidth() * fb.getHeight(); i++) {
            file.put(data[i].r);
            file.put(data[i].g);
            file.put(data[i].b);
        }
        
        file.close();
        return true;
    }
};

#endif // PPM_H
