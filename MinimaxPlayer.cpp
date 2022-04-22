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
using namespace std;

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

int MinimaxPlayer::utility(OthelloBoard b) {
	// calculate the AI's score (P2) against the human (P1) 
	int utility = b.count_score(b.get_p1_symbol()) - b.count_score(b.get_p2_symbol());
	return utility;
}

vector<OthelloBoard*> MinimaxPlayer::next_moves(OthelloBoard b, char symbol) {
	vector<OthelloBoard*> action_state;
	for (int i = 0; i < b.get_num_cols(); i++) {
		for (int j = 0; j < b.get_num_rows(); j++) {
			if (b.is_legal_move(i, j, symbol)) {
				// temporarily move pieces into the next "action" state
				OthelloBoard * explore = new OthelloBoard(b);
				explore->play_move(i, j, symbol);
				explore->set_col(i);
				explore->set_row(j);
				action_state.push_back(explore);
			}
		}
	}
	return action_state;
}

int MinimaxPlayer::max_value(OthelloBoard b) {
	if (!b.has_legal_moves_remaining(b.get_p2_symbol()) && b.has_legal_moves_remaining(b.get_p1_symbol())) {
		return utility(b);
	}
	int v = INT_MIN;
	char s = b.get_p1_symbol();
	vector<OthelloBoard*> nextstates = next_moves(b, s);
	for (int i = 0; i < nextstates.size(); i++) {
		v = max(v, min_value(*nextstates[i]));
	}
	return v;
}

int MinimaxPlayer::min_value(OthelloBoard b) {
	if (!b.has_legal_moves_remaining(b.get_p2_symbol()) && b.has_legal_moves_remaining(b.get_p1_symbol())) {
		return utility(b);
	}
	int v = INT_MAX;
	char s = b.get_p1_symbol();
	vector<OthelloBoard*> nextstates = next_moves(b, s);
	for (int i = 0; i < nextstates.size(); i++) {
		v = min(v, max_value(*nextstates[i]));
	}
	return v;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // Given the state of a game, calculate the best move by searching forward
	// all the way to the terminal states.
	int best_row, best_column = 0;
	int best_min = 9;
	int val;
	std:vector<OthelloBoard*> possible_moves = next_moves(*b, get_symbol());
	for (int i = 0; i < possible_moves.size(); i++) {
		val = max_value(*possible_moves[i]);
		if (val < best_min) {
			best_min = val;
			best_column = possible_moves[i]->get_col();
			best_row = possible_moves[i]->get_row();
		}
	}
	col = best_column;
	row = best_row;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}