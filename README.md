# snowflake

A minimal C-based simulation demonstrating snowflake crystal growth, Mullins-Sekerka instability, and dendritic faceting via Diffusion-Limited Aggregation (DLA) and surface attachment kinetics on a hexagonal lattice. Built with Raylib.

## Dependencies
- `gcc`
- `raylib`

## Build & Run
#### For Linux - 
```bash
make -f Makefile.linux
./snowflake
```

#### For Windows - 
- Download the **64-bit** version of `w64devkit` from its [official GitHub releases](https://github.com/skeeto/w64devkit/releases).
- Extract the zip file and double-click `w64devkit.exe` to open the terminal.
- Navigate to the cloned repo and run:
```bash
make
./snowflake.exe
```

#### For macOS -
Install raylib using Homebrew, then use the provided Mac Makefile:
```bash
brew install raylib
make -f Makefile.mac
./snowflake
```
