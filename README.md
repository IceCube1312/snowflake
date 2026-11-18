<img width="1920" height="1080" alt="20261114_12h18m34s_grim" src="https://github.com/user-attachments/assets/4a7ba62b-128c-455c-ae18-f962a95bbb82" />
<img width="1920" height="1080" alt="20261118_19h13m57s_grim" src="https://github.com/user-attachments/assets/233c625a-a586-4872-a321-0b00f128ddba" />
<img width="1920" height="1080" alt="20261113_15h13m21s_grim" src="https://github.com/user-attachments/assets/f3736f05-b039-4f27-a656-b885dc27faf2" />

# snowflake

A C based simulation where I try to simulate the mechanics of actual snowflake formation and growth by minimally modelling vapour diffusion, coordination dependant sticking probability and Mullins Sekerka instability.
Inspired from Brownian trees and modified to make beautiful and nice snowflakes.

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
