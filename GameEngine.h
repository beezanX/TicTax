// GameEngine.h

#ifndef GAME_ENGINE_H 
#define GAME_ENGINE_H

#include <iostream>
#include <string>  

class Game {
public:
	// Publicly accessible symbolic constants for players
	// Static const members can be initialized in-class if they are of integral type.
	static const int PLAYER_X_SYMBOL = 1; // Added const
	static const int PLAYER_O_SYMBOL = 2;
	static const int EMPTY_SYMBOL = 0;

	// Game constructor
	Game() {
		GenerateBoard();
		//std::cout << "test";
	}

	void displayBoard() const;
	void GenerateBoard();
	bool getEmptyCells(int row, int column) const;
	void Move(int row, int column, int playerMove);
	bool checkForWin(int player) const;
	bool checkForBlock(int player) const;
	void makeHypotheticalMove(int row, int column, int player);
	void undoMove(int row, int column);
	void makeComputerMove(int player);
	int opponentPlayer(int player) const;
	bool checkDraw() const;
	int getCellState(int row, int column) const;

	bool saveGame(const std::string& filename, int currentPlayerToSave, int moveCountToSave) const;
	bool loadGame(const std::string& filename, int& loadedPlayer, int& loadedMoveCount);

private:
	// Private constants for internal use, initialized from the public static ones
	// This ensures they always have the same values and gives a single point of definition.
	const int playerX = PLAYER_X_SYMBOL;
	const int playerO = PLAYER_O_SYMBOL;
	const int empty = EMPTY_SYMBOL;
	int board[3][3]; // actual board

	/*
	computer randomly pick from winningLines[8][x][y] x range is 0 to 3 and y range is 0 to 2
	computer picked {x=2, y=2}
	human picked {1, 1}
	computer check winninglines for {2, 2}
	computer {x, 2} ( random 0 to 1 ) e.g ( computer picked {1,2} )
	human picked {0,2}
	computer check winninglines and compare with human moves
	human moves : {1, 1}, {0,2}
	find these moves in winninglines
	computer check winningLines[8]
	computer found two matching human cells
	computer choose unused cell {2,0}
	human picked: {2,1}

	- current moves:
	human : {1, 1}, {0,2}, {2,1}
	computer : {2, 2}, {1,2}, {2,0}

	computer check winningLines[8]
	computer found two matching human cells
	computer choose unused cell {0, 1}

	- current moves:
	human : {1, 1}, {0,2}, {2,1}
	computer : {2, 2}, {1,2}, {2,0}, {0, 1}


	left: 2 moves to win

	computer find available cells
	computer random pick {1,0} or {0,0}

	human pick remained cell {1,0} or {0,0}



	*/

	const int winningLines[8][3][2] = {
		// human picked this {2,2} - search for { 2,2 } and return arrays
		// human potiential winning lines after humans first move would be row 3 and column 3

		// Rows
		{{0, 0}, {0, 1}, {0, 2}}, // 1
		{{1, 0}, {1, 1}, {1, 2}}, // 2
		{{2, 0}, {2, 1}, {2, 2}}, // 3
		// Columns
		{{0, 0}, {1, 0}, {2, 0}}, // 1
		{{0, 1}, {1, 1}, {2, 1}}, // 2
		{{0, 2}, {1, 2}, {2, 2}}, // 3
		// Diagonally
		{{0, 0}, {1, 1}, {2, 2}}, // 1
		{{0, 2}, {1, 1}, {2, 0}} // 2
	};

};

#endif // GAME_ENGINE_H