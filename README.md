# LimitLit

**LimitLit** is a deliberately limited software renderer inspired by the creative spirit of 1990s rendering tools.

## v0.2.0

This version adds the first real 2D drawing tools:

- Software framebuffer
- Pixel drawing
- Lines
- Rectangles
- Filled rectangles
- Simple startup/editor screen drawn by LimitLit
- SDL2 only used for the window and presenting pixels

## Build on Ubuntu

```bash
sudo apt update
sudo apt install cmake g++ pkg-config libsdl2-dev
mkdir -p build
cd build
cmake ..
make
./LimitLit
```

## Philosophy

Boundaries create creativity.
