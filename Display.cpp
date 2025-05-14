#include "GameEngine.h"
#include <iostream>


// Display Start

bool Game::checkDraw() const {
	// If 9 moves made and no winner, it's a draw.
	// if any empty cells remain.
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			if (board[r][c] == empty) {
				return false; // Found an empty cell, not a draw
			}
		}
	}
	// No empty cells found. Check if someone has already won (edge case)
	if (checkForWin(playerX) || checkForWin(playerO)) {
		return false;
	}
	return true; // Board is full, and no one won
}


void Game::displayBoard() const { // Use const because it doesn't change the board
	std::cout << "\n  CURRENT BOARD:\n";
	std::cout << "   0   1   2 \n"; // Column numbers
	std::cout << "  -----------\n";
	for (int row = 0; row < 3; ++row) {
		std::cout << row << "| "; // Row number
		for (int column = 0; column < 3; ++column) {
			char symbol = ' '; // Default to space, will be replaced

			// Access the private member variable 'board'
			int cellState = board[row][column];

			// Check the state against the private constants
			if (cellState == playerX) { // playerX is 1
				symbol = 'X';
			}
			else if (cellState == playerO) { // playerO is 2
				symbol = 'O';
			}
			else if (cellState == empty) { // empty is likely 0
				symbol = '-'; // Use '-' for empty cells
			}
			else {
				symbol = '?'; // Should not happen, indicates an error state
			}

			// Print the symbol for the cell, with separators
			std::cout << symbol << " | ";
		}
		// End of the row, print a newline and the separator line
		std::cout << "\n  -----------\n";
	}
	std::cout << std::endl; // Add an extra blank line for better spacing
}

// Display End