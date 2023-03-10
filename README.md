# Snake 🐍

<p align="center">
  <br>
  <img src="./example/screenshot.png" width="50%"/>
</p>

It's just snake.

## Installation

You need `make` and `cmake` for compiling.
On Ubuntu, install them with
```bash
sudo apt-get install build-essential cmake
```

You will also need to install the ncurses library.
On Ubuntu, you can do this via
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

Then, you compile by running
```bash
cmake -B./build && cd build
make -j$(nproc)
```

## Usage

After compiling, simply run
```bash
./build/snake
```
from the project root.

You control the snake with the <kbd>WASD</kbd>-keys.
Quit the game using the <kbd>Q</kbd> key.

Have fun! 🍎
