// main.cpp

#include "GameEngine.h" // Contains the declaration for our 'Game' class
#include <iostream>
#include <vector>       // Provides dynamic arrays (not directly used here but good to keep if from template)
#include <limits>       // For 'numeric_limits', used for robust input clearing
#include <stdexcept>    // For standard exception types
#include <fstream>      // For basic file stream operations

using namespace std;

// Constant integer values to represent the players.
const string SAVE_FILENAME = "tictactoe_save.txt";

// This is the 'main' function, the starting point for execution.
int main() {
    try {
        Game game; // Creates an instance of our 'Game' class (constructor calls GenerateBoard)

        // We are calling variables inside our Game class
        int currentPlayer = Game::PLAYER_X_SYMBOL; // Human plays as X
        const int PLAYER_HUMAN = Game::PLAYER_X_SYMBOL;
        const int PLAYER_COMPUTER = Game::PLAYER_O_SYMBOL;
        int moveCount = 0;                // Tracks the total number of moves.
        bool gameOver = false;            // Flag to indicate if the game has ended.

        // Welcome message and game instructions.
        cout << "=====================\n";
        cout << " TicTaX (Console Version)\n";
        cout << " Human (X) vs Computer (O)\n";
        cout << "=====================\n";

        // Ask to load a saved game
        cout << "Load a saved game from '" << SAVE_FILENAME << "'? (y/n): ";
        char loadChoice;
        cin >> loadChoice;

        // Clear the input buffer after reading a character
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (loadChoice == 'y' || loadChoice == 'Y') {
            if (game.loadGame(SAVE_FILENAME, currentPlayer, moveCount)) {
                cout << "Game successfully loaded." << endl;
                // Check if the loaded game is already over
                if (game.checkForWin(PLAYER_HUMAN) || game.checkForWin(PLAYER_COMPUTER) || (moveCount >= 9 && game.checkDraw())) {
                    cout << "The loaded game is already complete." << endl;
                    gameOver = true; // Set gameOver if loaded state is already a finished game
                }
            }
            else {
                cout << "Failed to load game or no save file found. Starting a new game." << endl;
                // game.GenerateBoard(); // Constructor already called this
                currentPlayer = PLAYER_HUMAN; // Reset to default for a new game
                moveCount = 0;             // Reset to default for a new game
            }
        }
        else {
            cout << "Starting a new game." << endl;
            // Ensure board is fresh if not loading (though constructor handles this)
            // and player/moveCount are at their initial new-game state.
            // game.GenerateBoard(); // Already done by constructor
            currentPlayer = PLAYER_HUMAN;
            moveCount = 0;
        }

        if (!gameOver) { // Only print instructions if not loading an already finished game
            cout << "Enter row and column (e.g., 1 1 for center), separated by space.\n";
        }


        // Main game loop: continues as long as 'gameOver' is false.
        while (!gameOver) {
            game.displayBoard(); // Display the current state of the board.

            if (currentPlayer == PLAYER_HUMAN) {
                // --- Human Player's Turn ---
                int inputRow = -1, inputColumn = -1; // Variables for human's row and column input.
                bool validInput = false;          // Flag for valid move input.

                while (!validInput) {
                    cout << "Your move (row column): ";
                    cin >> inputRow >> inputColumn;

                    if (cin.fail()) {
                        cout << "Invalid input. Please enter two numbers (0-2).\n";
                        cin.clear(); // Clear error flags.
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input.
                    }
                    else if (inputRow < 0 || inputRow > 2 || inputColumn < 0 || inputColumn > 2) {
                        cout << "Invalid input. Row and column must be between 0 and 2.\n";
                    }
                    else if (!game.getEmptyCells(inputRow, inputColumn)) {
                        cout << "Cell (" << inputRow << ", " << inputColumn << ") is already taken. Try again.\n";
                    }
                    else {
                        validInput = true; // Input is valid.
                    }
                }
                game.Move(inputRow, inputColumn, PLAYER_HUMAN); // Update board with human's move.
            }
            else {
                // --- Computer Player's Turn ---
                cout << "\nComputer thinking...\n";
                game.makeComputerMove(PLAYER_COMPUTER); // AI makes its move.
                cout << "Computer moved." << endl;
            }

            moveCount++; // Increment move counter.

            // --- Check for Game Over Conditions ---
            if (game.checkForWin(currentPlayer)) {
                game.displayBoard(); // Display final board.
                cout << "\n=====================\n";
                if (currentPlayer == PLAYER_HUMAN) {
                    cout << "  Congratulations! You (X) win!\n";
                }
                else {
                    cout << "  Computer (O) wins!\n";
                }
                cout << "=====================\n";
                gameOver = true;
            }
            else if (moveCount == 9) { // Board is full (or should be)
                // checkDraw also verifies no winner, which is a good final check
                if (game.checkDraw()) {
                    game.displayBoard(); // Display final board.
                    cout << "\n=====================\n";
                    cout << "  It's a draw!\n";
                    cout << "=====================\n";
                    gameOver = true;
                }
                // If checkDraw is false, it means someone won on the 9th move,
                // which should have been caught by the checkForWin(currentPlayer) above.
            }

            // If game is not over, switch player and offer to save
            if (!gameOver) {
                currentPlayer = game.opponentPlayer(currentPlayer);

                cout << "Save game to '" << SAVE_FILENAME << "'? (y/n, or any other key to continue): ";
                char saveChoice;
                cin >> saveChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                if (saveChoice == 'y' || saveChoice == 'Y') {
                    if (game.saveGame(SAVE_FILENAME, currentPlayer, moveCount)) {
                        // Optionally, you could add a message here confirming save
                    }
                    else {
                        cout << "Failed to save game." << endl;
                    }
                }
            }
        } // End of main game loop

    }
    catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1; // Indicate error termination.
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
        return 1; // Indicate error termination.
    }

    cout << "\nGame finished. Press Enter to exit." << endl;
    // Ensure any leftover newline from a previous cin is handled before cin.get()
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    cin.get(); // Wait for Enter key press.

    return 0; // Indicate successful program execution.
}