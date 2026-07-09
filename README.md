# LimitLit

A deliberately limited software renderer inspired by 1990s creative rendering tools.

## v0.8.0

UI polish release:

- Persistent selected Sphere tool
- Hover and pressed button states
- Stronger visual hierarchy
- Warmer panels and blue-gray accents
- Scene list section
- Properties grouped into sections
- More finished status bar
- Existing CPU ray tracer retained

## Build

```bash
sudo apt install cmake g++ pkg-config libsdl2-dev
mkdir -p build
cd build
cmake ..
make
./LimitLit
```
