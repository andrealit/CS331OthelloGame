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
	return b->count_score(symbol);
}

vector<State*> MinimaxPlayer::successor(OthelloBoard* b, char symbol) {
	vector<State*> action_state;
	for (int i = 0; i < b->get_num_cols(); i++) {
		for (int j = 0; j < b->get_num_rows(); j++) {
			if (b->is_legal_move(i, j, symbol)) {
				// temporarily move pieces into the next "action" state
				Move* move = new Move(i, j);
				OthelloBoard* explore = new OthelloBoard(*b);
				explore->play_move(move->col, move->row, symbol);
				action_state.push_back(new State(explore, move));
			}
		}
	}
	return action_state;
}

char MinimaxPlayer::opponent(char symbol) {
	char ops = (symbol == 'X') ? 'O' : 'X';
	return ops;
}

Node* MinimaxPlayer::minimax_decision(OthelloBoard* b, char symbol, bool max) {
	vector<State*> nextmoves = successor(b, symbol);
	char op = opponent(symbol);

	if (nextmoves.empty()) {
		return new Node(NULL, utility(b));
	}

	if (max) { // max_value
		Node* best = max_value(b, nextmoves, op);
		return best;
	}
	else { // min_value
		Node* best = min_value(b, nextmoves, op);
		return best;
	}
}

Node* MinimaxPlayer::max_value(OthelloBoard* b, vector<State*> nextmoves, char op) {
	Node* best = new Node(NULL, INT_MIN);
	for (vector<State*>::iterator i = nextmoves.begin(); i != nextmoves.end(); i++) {
		Node* v = minimax_decision((*i)->board, op, false);

		if (v->score > best->score) {
			best = new Node((*i)->move, v->score);
		}
	}
	return best;
}

Node* MinimaxPlayer::min_value(OthelloBoard* b, vector<State*> nextmoves, char op) {
	Node* best = new Node(NULL, INT_MAX);
	for (vector<State*>::iterator i = nextmoves.begin(); i != nextmoves.end(); i++) {
		Node* v = minimax_decision((*i)->board, op, true);

		if (v->score < best->score) {
			best = new Node((*i)->move, v->score);
		}
	}
	return best;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // Given the state of a game, calculate the best move by searching forward
	// all the way to the terminal states.

	// use minimax_decision
	Node* choice = minimax_decision(b, symbol, true);

	// assign rows and columns
	col = choice->move->col;
	row = choice->move->row;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}