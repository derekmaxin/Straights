#ifndef _PLAYER_H_
#define _PLAYER_H

#include <vector>
#include <string>

//#include "card.h"
#include "component.h"

class Player : public Component {
	vector<Card> hand;
	vector<Card> discard;
	Board board;
	public:
	int score;

	Player(vector<Card> hand, Board board); //constructor

	string play(vector<Card>, Board board);
	int addToScore(int score);
};

#endif
