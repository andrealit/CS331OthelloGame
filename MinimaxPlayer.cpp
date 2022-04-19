/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 *  Edited on: Apr 19, 2022
 * 		Author: Andy Tongsak
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

/**
 * What we need:
 * Adversarial search utilizes -
 * Score of the current state
 * Utility function that returns a vector of utilities
 * Expand all the possible states
 */

int MinimaxPlayer::utility(OthelloBoard* b) {
	// calculate the AI's score (P2) against the human (P1) 
	int utility = b->count_score(b->get_p1_symbol() - b->count_score(b->get_p2_symbol()));
	return utility;
}



void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // Given the state of a game, calculate the best move by searching forward
	// all the way to the terminal states.

	// Generate every possible state on every move
	void max_value(OthelloBoard* b) {
		
	}

	void min_value(OthelloBoard* b) {

	}

	

	// @todo Implement the get_move function using the minimax algorithm psuedocode

}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}

// makes a backup board, then adds it to a vector
// OthelloBoard *backupBoard = new OthelloBoard(*b)
