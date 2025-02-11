# EmuMouse

EmuMouse is a lightweight Windows utility that emulates mouse wheel scrolling using keyboard shortcuts. Perfect for users with malfunctioning mouse wheels or those who prefer keyboard-based scrolling.

## Features

- Emulates mouse wheel using keyboard shortcuts:
- Works with any application or game
- Compatible with modifier keys (Shift, Ctrl, Alt)
- Written in C++, which means low CPU and RAM usage
- Works in background without UI
- Zero configuration needed

## Why Use It?

- Your mouse wheel is broken or malfunctioning
- You prefer keyboard-based scrolling
- You want to reduce wear on your mouse wheel

## How It Works

The program runs in the background and listens for the following key combinations:
- `Windows + Q`: Simulates mouse wheel scroll up
- `Windows + A`: Simulates mouse wheel scroll down

## Installation

1. Download the latest release from [Releases](../../releases)
2. Run `EmuMouse.exe`
3. Start using Win+Q and Win+A for scrolling

## Building from Source

Requirements:
- MinGW-w64 or other C++ compiler with Windows API support
- Windows SDK

### Compile resources
windres resource.rc -O coff -o resource.res

### Compile program
g++ -o EmuMouse.exe mouse.cpp resource.res -mwindows

## Auto-start with Windows
To make the program start automatically with Windows:

- Press Win + R
- Type `shell:startup`
- Copy EmuMouse.exe in the opened folder

## License
[CC BY-NC 4.0](LICENSE)

This software is licensed under Creative Commons Attribution-NonCommercial 4.0 International License. This means you can freely use and modify the code for non-commercial purposes, as long as you provide attribution to the original author.

Commercial use is prohibited without explicit permission from the author.

## Author
ran4erep

Last updated: 2025-02-11

![](mouse.gif)
