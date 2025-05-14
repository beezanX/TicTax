# TicTaX - Console Tic-Tac-Toe

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) *(Optional: Add a license badge if you choose the MIT license or another)*

This project is a command-line implementation of the classic game Tic-Tac-Toe (also known as Noughts and Crosses). Play against a computer opponent that uses programmed strategies to make its moves, and utilize save/load functionality to resume games.

This game was developed as a school project to demonstrate basic C++ programming concepts, object-oriented design, and file I/O.

## Table of Contents

- [Features](#features)
- [How to Build](#how-to-build)
- [How to Run](#how-to-run)
- [How to Play](#how-to-play)
- [Computer Opponent Logic](#computer-opponent-logic)
- [File Structure](#file-structure)
- [Technologies Used](#technologies-used)
- [Author](#author)
- [License](#license)

## Features

* **Human vs. Computer Gameplay:** Play against a single computer opponent.
* **Console Interface:** Interact with the game directly through your terminal.
* **Strategic Computer Opponent:** The computer uses a set of defined strategies to determine its moves.
* **Save and Load Game:** Save your current game progress to a file and load it later to resume where you left off.
* **Win and Draw Detection:** Accurately identifies winning conditions for both players and detects a draw when the board is full.

## How to Build

To build this project, you will need a C++ compiler (such as g++ or Clang) and the standard C++ library.

1.  **Clone the repository** (or download the source code files) to your local machine.
2.  **Open your terminal or command prompt** and navigate to the root directory of the project.
3.  **Compile the source files.** The exact command may vary slightly depending on your compiler, but for g++, you can use:

    ```bash
    g++ main.cpp GameEngine.cpp Display.cpp -o tictax -std=c++11
    ```
    *(Using `-std=c++11` or higher is recommended for modern C++ features).*

    This command compiles the `main.cpp`, `GameEngine.cpp`, and `Display.cpp` files and links them into an executable named `tictax` (or `tictax.exe` on Windows).

## How to Run

After successfully building the project, you can run the executable from your terminal:

```bash
./tictax
