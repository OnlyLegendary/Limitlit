# LimitLit

A deliberately limited software renderer inspired by 1990s creative rendering tools.

## v0.7.0

This release improves the first CPU ray-traced render:

- Ray-traced sphere
- Ground plane ray intersection
- Contact shadow
- Cast shadow
- Sky/ground ambient lighting
- Ground bounce tint on sphere
- Mild distance haze
- The ray tracer now owns the full viewport image

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
