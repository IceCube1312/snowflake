<img width="1920" height="1080" alt="20261113_23h32m29s_grim" src="https://github.com/user-attachments/assets/f6bbd5cb-5d87-41b9-8899-9e8a7e1ffa5f" />
<img width="1920" height="1080" alt="20261113_14h47m43s_grim" src="https://github.com/user-attachments/assets/53d1f521-a73f-4515-a8e8-b7f6b7a09a66" />
<img width="1920" height="1080" alt="20261113_15h13m21s_grim" src="https://github.com/user-attachments/assets/f3736f05-b039-4f27-a656-b885dc27faf2" />
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
