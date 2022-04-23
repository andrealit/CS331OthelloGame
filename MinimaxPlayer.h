/*
 * MinimaxPlayer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */

#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "Player.h"
#include <vector>
using std::vector;

class Move {
	public:
		int col;
		int row;
		Move(int c, int r) {
			this->col = c;
			this->row = r;
		}
	private:

};

class Node {
	public:
		Move* move;
		int score;
		Node(Move* m, int s) {
			this->move = m;
			this->score = s;
		}
	private:
};

class State {
	public:
		Move* move;
		OthelloBoard* board;
		State(OthelloBoard* b, Move* m) {
			this->board = b;
			this->move = m;
		}
	private:
};

/**
 * This class represents an AI player that uses the Minimax algorithm to play the game
 * intelligently.
 */
class MinimaxPlayer : public Player {
public:

	/**
	 * @param symb This is the symbol for the minimax player's pieces
	 */
	MinimaxPlayer(char symb);

	/**
	 * Destructor
	 */
	virtual ~MinimaxPlayer();

	/**
	 * @param b The board object for the current state of the board
	 * @param col Holds the return value for the column of the move
	 * @param row Holds the return value for the row of the move
	 */
    void get_move(OthelloBoard* b, int& col, int& row);

	/**
	 * @param b The board object for the current state of the board
	 */
	int utility(OthelloBoard* b);

	/**
	 * @param b The board object for the current state of the board
	 */
	vector<State*> successor(OthelloBoard* b, char symbol);

	/**
	 * @param symbol 
	 * @return character of the opponent symbol
	 */
	char opponent(char symbol);

	/**
	 * @param b 
	 * @param symbol 
	 * @param max 
	 * @return Node* 
	 */
	Node* minimax_decision(OthelloBoard* b, char symbol, bool max);

	/**
	 * @param b The board object for the current state of the board
	 */
	Node* max_value(OthelloBoard* b, vector<State*> nm, char osymbol);

	/**
	 * @param b The board object for the current state of the board
	 */
	Node* min_value(OthelloBoard* b, vector<State*> nm, char osymbol);

    /**
     * @return A copy of the MinimaxPlayer object
     * This is a virtual copy constructor
     */
    MinimaxPlayer* clone();

	
private:

};


#endif
