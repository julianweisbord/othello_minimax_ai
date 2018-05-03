
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

vector<OthelloBoard*> MinimaxPlayer::get_successors(OthelloBoard* b, char player_symb){
	/*
	For a given player symbol, iterate through the board and generate all possible states
	*/
	// Create a vector of boards
	vector <OthelloBoard* > board_choices;
	// Loop through each posible move on the board and create a board
	//   state for that move.
	for(int x = 0; x < b->get_row_len(); ++x){
		for(int y = 0; y < b->get_col_len(); ++y){

			if(b->is_legal_move(x, y, player_symb)){
				OthelloBoard* successor = new OthelloBoard(*b);
				// std::cout << "New Successor board" << std::endl;
				// Add successor to board vector and make move
				board_choices.insert(board_choices.begin(), successor);
				board_choices.front()->play_move(x, y, player_symb);
				board_choices.front()->set_row_pos(y);
				board_choices.front()->set_col_pos(x);
			}
		}
	}
	return board_choices;
}

void MinimaxPlayer::get_move(OthelloBoard *b, int &col, int &row) {
	// To be filled in by you
	decision(b, col, row);

}

void MinimaxPlayer::decision(OthelloBoard *b, int &col, int &row){
	if (symbol == b->get_p1_symbol()) {
		calc_max(b, col, row, 'X');
		// calc_min(b, col, row, 'X');
	}
	else{
		calc_max(b, col, row, 'O');
	}
}

int MinimaxPlayer::terminal_test(vector <OthelloBoard*> board, OthelloBoard *b){
	// std::cout << board.size << std::endl;
	if (board.size() < 1) {
		return calc_utility(b);
	}
}

int MinimaxPlayer::calc_max(OthelloBoard *b, int &column, int &row,  char playerSymb) {
	int max_val = INT_MIN;
	int i = 0;
	int check = 0;

	vector <OthelloBoard* > board;
	// Get possible moves for the current player
	if (playerSymb == 'O') {
		board = get_successors(b, 'O');}

	// If the list is empty, this is terminal state
	if (board.size() < 1) {
		return calc_utility(b);
	}
	// int terminal_score = terminal_test(board, b);
	// if (terminal_score){
	// 	return terminal_score;
	// }
	int max_row, max_column;
	// Iterate through the sucessors vector and
	// calculate the max value recursively.
	do{
		// if(max_val < calc_max(board[i], column, row, playerSymb)) {
			// Found new max value, swap
			// std::cout<< "Found new max!!!" << std::endl;
		int prev_max = max_val;
		max_val =	std::max(prev_max, calc_max(board[i], column, row, playerSymb));
		// max_val = calc_max(board[i], column, row, playerSymb);
		if(prev_max != max_val){
			max_row = board[i]->get_row_pos();
			max_column = board[i]->get_col_pos();
		}
		i += 1;
	}while(i < board.size());
	// Update references to hold the row and col of the minimum
	row = max_row;
	column = max_column;
	// assert(col >= 0);
	// assert(row >= 0);
	return max_val;
}


int MinimaxPlayer::calc_min(OthelloBoard *b, int &column, int &row, char playerSymb) {
	int min_val = INT_MAX;
	int i = 0;
	int check = 0;

	vector <OthelloBoard*> board;
	// Get possible moves for the current player
	if (playerSymb == 'O') {
		board = get_successors(b, 'O');}

	// If the list is empty, this is terminal state
	if (board.size() < 1) {
		return calc_utility(b);
	}
	// int terminal_score = terminal_test(board, b);
	// if (terminal_score){
	// 	return terminal_score;
	// }

	int min_row, min_column;
	do{
			int prev_min = min_val;
			min_val = std::min(prev_min, calc_min(board[i], column, row, playerSymb));
			// std::cout<< "Found new min!!!" << std::endl;
			if (prev_min != min_val){
				min_row = board[i]->get_row_pos();
				min_column = board[i]->get_col_pos();

			}
			i += 1;
	} while(i < board.size());
	// Update references to hold the row and col of the minimum
	row = min_row;
	column = min_row;
	// assert(col >= 0);
	// assert(row >= 0);
	return min_val;
}

int MinimaxPlayer::calc_utility(OthelloBoard* b){
	/*
	Given any board state calculate how well the computer is doing compared
		to the player.
	*/
	// Score of computer
	int comp_score = b->count_score(b->get_p2_symbol());
	// Score of player
	int human_score = b->count_score(b->get_p1_symbol());
	// Compute difference
	return  human_score - comp_score;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
