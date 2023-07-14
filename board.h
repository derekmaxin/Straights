#include <vector>
#include <string>

#include "card.h"

class Board {
	public:
	vector<Card> spades;
	vector<Card> clubs;
	vector<Card> hearts;
	vector<Card> diamonds;

	//Board();//constructor

	bool playCard(Card);
};
