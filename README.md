# TicTaX - Console Tic-Tac-Toe Game 👋

This project is a command-line implementation of the classic game Tic-Tac-Toe (also known as Noughts and Crosses). Play against a computer opponent that uses programmed strategies to make its moves, and utilize save/load functionality to resume games.

![image](https://github.com/user-attachments/assets/726208ac-5367-4d89-b060-80892a253c0d)

This game was developed as a school project to demonstrate basic C++ programming concepts, object-oriented design, and file I/O.

## Table of Contents 📜
* [Features](#features-)
* [How to Build](#how-to-build-%EF%B8%8F)
* [How to Play](#how-to-play-)
* [Computer Opponent Logic](#computer-opponent-logic-)
* [Author](#author-%EF%B8%8F)
* [License](#license-)

## Features ✨
*   **Human vs. Computer Gameplay:** Play against a single computer opponent. 🤖
*   **Console Interface:** Interact with the game directly through your terminal. 🖥️
*   **Strategic Computer Opponent:** The computer uses a set of defined strategies to determine its moves. 🤔
*   **Save and Load Game:** Save your current game progress to a file and load it later to resume where you left off. 💾
*   **Win and Draw Detection:** Accurately identifies winning conditions for both players and detects a draw when the board is full. ✅

## How to Build 🛠️
To build this project, you will need a C++ compiler (such as g++ or Clang) and the standard C++ library.

1.  **Clone the repository:**
    Open your terminal or command prompt and run:
    ```bash
    git clone <repository_url>
    ```
    (Replace `<repository_url>` with the actual URL of your GitHub repository)

2.  **Navigate to the project directory:**
    ```bash
    cd TicTaX
    ```

3.  **Compile the source files:**
    Using g++, you can compile with:
    ```bash
    g++ main.cpp GameEngine.cpp Display.cpp -o tictax -std=c++11
    ```
    (Using `-std=c++11` or higher is recommended for modern C++ features).

    This command compiles the necessary `.cpp` files and creates an executable named `tictax` (or `tictax.exe` on Windows).

## How to Play 🎮
1.  When you run the program, you will see a welcome message and the initial empty board.
2.  You will be prompted if you wish to load a saved game (`tictactoe_save.txt`). Enter `y` or `Y` to load, or any other key to start a new game.
3.  If starting a new game, you (Human) will play as 'X', and the Computer will play as 'O'.
4.  To make a move, enter the row and column numbers (0-indexed, from 0 to 2) separated by a space, and press Enter.
    *   Example: `0 0` for the top-left corner.
    *   Example: `1 1` for the center.
    *   Example: `2 0` for the bottom-left corner.
5.  The board will be displayed after each move.
6.  The computer will then make its move based on its programmed strategy.
7.  The game continues until one player gets three of their marks in a row (horizontally, vertically, or diagonally) or until all nine cells are filled (resulting in a draw). 🏁
8.  After each human move (unless the game is over), you will be asked if you want to save the current game state.
9.  Follow the on-screen prompts to play.

## Computer Opponent Logic 🤔
The computer opponent does not use machine learning or true artificial intelligence. Instead, it follows a set of predefined rules to choose its moves:

1.  It first checks if it can win in the current turn. If so, it makes the winning move.
2.  If it cannot win, it checks if the human player can win in their next turn and attempts to block that winning move.
3.  If neither player can win immediately, the computer prioritizes taking the center square.
4.  If the center is taken, it looks for an available corner square.
5.  If corners are also taken, it takes any available side square.

This strategic approach makes the computer a challenging, but predictable, opponent.
*   `Display.cpp`: Contains the implementation for displaying the game board in the console.
*   `GameEngine.cpp`: Contains the implementation of the core game logic and the computer opponent's move strategy.
*   `GameEngine.h`: Contains the class definition for `GameEngine`.
*   `main.cpp`: Contains the `main` function, game loop, and user input handling.


## Author ✍️
*   [beezanX](https://github.com/beezanX)

## License 📄
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project is open-source and available under the MIT License. You are free to use, modify, and distribute the code, provided you include the original copyright and license notice.
