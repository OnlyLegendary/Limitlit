# LimitLit

A deliberately limited software renderer inspired by 1990s creative rendering tools.

## v0.6.0

First actual ray tracing milestone:

- Vec3 math
- Ray type
- CPU ray tracer
- Ray/sphere intersection
- Simple diffuse lighting
- Ray-traced sphere rendered into the studio viewport
- UI still drawn into the same framebuffer

## Build

```bash
sudo apt update
sudo apt install cmake g++ pkg-config libsdl2-dev
mkdir -p build
cd build
cmake ..
make
./LimitLit
```
