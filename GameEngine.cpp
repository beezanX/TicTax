#include "GameEngine.h"
#include <iostream>
#include <fstream> // For ofstream and ifstream





// Generate board array (status:completed)
void Game::GenerateBoard() {
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			board[row][column] = EMPTY_SYMBOL;
		}
	}
}

int Game::getCellState(int row, int column) const {
	if (row >= 0 && row < 3 && column >= 0 && column < 3) {
		return board[row][column];
	}
	return -1; // Indicate error or invalid cell
}






// reading private members (status:completed)
bool Game::getEmptyCells(int row, int column) const {
	if (board[row][column] == 0) {
		// return (row, column) if cell is empty
		return true; // 1 means cell is empty
	}
	else {
		return false;
	}
}

// Get opponent Player
int Game::opponentPlayer(int player) const {
	int opponentPlayer;
	if (player == playerX) { // Assuming playerX is 1
		opponentPlayer = playerO; // Assuming playerO is 2
		return opponentPlayer;
	}
	opponentPlayer = playerX;
	return opponentPlayer;
}

// win status verification (status:completed)
bool Game::checkForWin(int computerPlayer) const {
	// loop through 8 possible winning lines
	for (int row = 0; row < 8; ++row) {
		bool switcher = true; // Assume this line is a winning one initially

		// Check the 3 cells for this line
		for (int column = 0; column < 3; ++column) {
			int r = winningLines[row][column][0]; // Get row for current cell in line
			int c = winningLines[row][column][1]; // Get col for current cell in line

			// If the cell on the board doesn't belong to the player...
			if (board[r][c] != computerPlayer) {
				switcher = false; // ...then this line is not a winning line
				break; // No need to check the rest of the cells in this line
			}
		}

		// If, after checking all 3 cells, lineWins is still true, we found a win
		if (switcher) {
			return true;
		}
	}

	// If the outer loop completes, no winning line was found
	return false;
}



// block status verification (status:completed)
bool Game::checkForBlock(int computerPlayer) const {

	int player = opponentPlayer(computerPlayer);
	// loop inside winninglines
	for (int row = 0; row < 8; ++row) {
		// Counting status
		int opponentCount = 0;
		int emptyCount = 0;

		// Check the 3 cells that make up the current winning line
		for (int column = 0; column < 3; ++column) {
			int r = winningLines[row][column][0]; // Get row for current cell in line
			int c = winningLines[row][column][1]; // Get col for current cell in line

			// Access the actual game state board
			// *** Ensure 'board[r][c]' refers to your int board[3][3] state array ***
			int cellState = board[r][c];

			// Count opponent marks and empty cells in this line
			if (cellState == player) {
				opponentCount++;
			}
			else if (cellState == empty) {
				emptyCount++;
			}
			// Note: We don't need to count the current player's pieces for blocking logic
		}

		// Check the block condition
		// If the opponent has exactly 2 marks AND the 3rd cell is empty
		if (opponentCount == 2 && emptyCount == 1) {
			return true; // block is necessary
		}
	}
	// loop completes without finding any line needing a block
	return false;
}





// Initialize move to array (status:completed)
void Game::Move(int row, int column, int playerMove) {
	board[row][column] = playerMove; // make a move
	//std::cout << board[row][column];
}







// Computer hypothetical move
void Game::makeHypotheticalMove(int row, int column, int player) { // row and column are the current move
	board[row][column] = player; // making a hypothetical move
}



void Game::undoMove(int row, int column) {
	board[row][column] = empty; // undo the move
}




void Game::makeComputerMove(int computerPlayer) {
	int opponent = opponentPlayer(computerPlayer); // Calculate opponent ID once

	// --- Stage 1: Check for Immediate Win ---
	// basically
	// The computer looks at every empty spot on the board. For each empty spot, it pretends to put its piece there. Then, it checks if that pretend move makes it win.
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			if (getEmptyCells(row, column)) { // Is the cell empty?
				makeHypotheticalMove(row, column, computerPlayer); // Try placing computer's piece
				bool computerWins = checkForWin(computerPlayer); // this function checks if one of winning lines is filled
				undoMove(row, column); // *** UNDO ***
				if (computerWins) {
					Move(row, column, computerPlayer); // Make the winning move
					return;                     // exit our function
				}
			}
		}
	}

	// --- Stage 2: Check for Immediate Block ---
	int blockRow = -1, blockCol = -1; // Variables to store blocking move coords
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			if (getEmptyCells(row, column)) { // Is the cell empty?
				makeHypotheticalMove(row, column, opponent); // Hypothetical OPPONENT move
				bool opponentWouldWin = checkForWin(opponent);
				undoMove(row, column); // undo Move
				if (opponentWouldWin) {
					blockRow = row; // Store block coordinates
					blockCol = column;
					goto found_block; // Exit loops once a block is found
				}
			}
		}
	}
found_block:; // Label for goto jump

	// --- Stage 3: Make the Move (Prioritized) ---
	if (blockRow != -1) { // Check if the blockRow is not -1
		Move(blockRow, blockCol, computerPlayer); // Make the blocking move
		return;
	}

	// --- Stage 4: Fallback Strategy ---
	// Try Center
	if (getEmptyCells(1, 1)) {
		Move(1, 1, computerPlayer);
		return;
	}

	// Try Corners (Implement logic to pick one available corner)
	int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
	for (int i = 0; i < 4; ++i) { // We check if the corners are available
		int cornerRow = corners[i][0];
		int cornerCol = corners[i][1];
		if (getEmptyCells(cornerRow, cornerCol)) {
			Move(cornerRow, cornerCol, computerPlayer);
			return;
		}
	}


	// Try Sides (Implement logic to pick one available side)
	int sides[4][2] = { {0, 1}, {1, 0}, {1, 2}, {2, 1} };
	for (int i = 0; i < 4; ++i) { // We check if the corners are available
		int sideRow = sides[i][0];
		int sideCol = sides[i][1];
		if (getEmptyCells(sideRow, sideCol)) {
			Move(sideRow, sideCol, computerPlayer);
			return;
		}
	}
}


// Save game function
bool Game::saveGame(const std::string& filename, int currentPlayerToSave, int moveCountToSave) const {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << " for saving." << std::endl;
		return false;
	}

	// Save board
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			outFile << board[row][column] << (column == 2 ? "" : " "); // Space separated
		}
		outFile << std::endl;
	}

	// Save current player and move count
	outFile << currentPlayerToSave << std::endl;
	outFile << moveCountToSave << std::endl;

	outFile.close();
	std::cout << "Game saved to " << filename << std::endl;
	return true;
}

// load game function
bool Game::loadGame(const std::string& filename, int& loadedPlayer, int& loadedMoveCount) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << " for loading." << std::endl;
		return false;
	}

	// Load board
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			if (!(inFile >> board[row][column])) { // Read and check for error
				std::cerr << "Error: Could not read board data from " << filename << std::endl;
				inFile.close();
				return false;
			}
		}
	}

	// Load current player and move count
	if (!(inFile >> loadedPlayer >> loadedMoveCount)) {
		std::cerr << "Error: Could not read player/move_count data from " << filename << std::endl;
		inFile.close();
		return false;
	}

	inFile.close();
	std::cout << "Game loaded from " << filename << std::endl;
	return true;
}

/*





// Player Move

int Game::getEmptyCells() {}
bool Game::isMoveValid(int row, int col) {}
bool Game::makeHypotheticalMove(int row, int col, int player) {}
// Check for winner
bool Game::checkForWin(int getBoardState()) {}
void Game::undoMove() {}

*/


