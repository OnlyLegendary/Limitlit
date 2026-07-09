# LimitLit

**LimitLit** is a deliberately limited software renderer inspired by the creative spirit of 1990s rendering tools.

## v0.5.0

This release adds the first "world" viewport:

- Native OS mouse cursor restored
- Software UI still drawn into the framebuffer
- Sky gradient
- Sun disk
- Horizon
- Ground plane
- Perspective grid
- Startup world feeling instead of an empty viewport

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

Press `Esc` to close.
