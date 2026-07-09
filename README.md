# LimitLit

**LimitLit** is a deliberately limited software renderer inspired by the creative spirit of 1990s rendering tools.

## v0.4.0

This release adds early interaction and a more complete editor shell:

- Mouse state tracking
- Hovered buttons
- Pressed button effect
- Status bar changes based on hover
- Software-drawn cursor
- Welcome message in the viewport
- Classic 90s style UI drawn entirely into the framebuffer

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
