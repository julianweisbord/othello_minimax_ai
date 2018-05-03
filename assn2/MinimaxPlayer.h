
#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "Player.h"
#include <vector>
using std::vector;

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
		void decision(OthelloBoard*, int&, int&);
		int calc_utility(OthelloBoard* );
		vector<OthelloBoard* > get_successors(OthelloBoard*, char);
		int terminal_test(vector <OthelloBoard*>, OthelloBoard *);
		int calc_max(OthelloBoard *, int &, int &,  char);
		int calc_min(OthelloBoard *, int &, int &, char);
		/**
	 * @return A copy of the MinimaxPlayer object
	 * This is a virtual copy constructor
	 */
    MinimaxPlayer* clone();

private:

};


#endif
