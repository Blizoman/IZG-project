# IZG-project

A computer graphics project implementing basic 2D rendering primitives and algorithms.

## Description

This project demonstrates fundamental computer graphics concepts including:
- 2D and 3D vector mathematics
- Color representation and manipulation
- Framebuffer management
- 2D graphics primitives (lines, circles, rectangles, triangles)
- Image output in PPM format

## Features

- **Vector Math**: 2D and 3D vector operations (addition, subtraction, dot product, cross product, normalization)
- **Color System**: RGB color representation with interpolation support
- **Framebuffer**: In-memory image buffer for rendering
- **Graphics Primitives**:
  - Line drawing (Bresenham's algorithm)
  - Circle drawing (Midpoint circle algorithm)
  - Rectangle drawing and filling
  - Triangle drawing
- **Image Export**: PPM file format support

## Building

The project uses CMake for building. To compile:

```bash
mkdir build
cd build
cmake ..
make
```

## Running

After building, run the executable:

```bash
./bin/izg_project
```

This will generate an `output.ppm` file with a demonstration of various graphics primitives.

## Project Structure

```
IZG-project/
├── include/          # Header files
│   ├── vector.h      # Vector mathematics
│   ├── color.h       # Color definitions
│   ├── framebuffer.h # Framebuffer class
│   ├── graphics.h    # Graphics primitives
│   └── ppm.h         # PPM file writer
├── src/              # Source files
│   └── main.cpp      # Main program
├── CMakeLists.txt    # Build configuration
└── README.md         # This file
```

## Requirements

- C++17 compatible compiler
- CMake 3.10 or higher

## Author

Andrej Bližnák (xblizna00@stud.fit.vut.cz)

## License

Educational project for IZG course at VUT FIT.