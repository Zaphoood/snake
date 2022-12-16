# Snake 🐍

It's just snake. What did you expect?

Well, it does run in your terminal so I guess that's kinda cool.

## Installation

You will need to install the ncurses library.

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

You control the snake with the `WASD`-keys.
Quit the game using the `Q` key.

Have fun! 🍎
