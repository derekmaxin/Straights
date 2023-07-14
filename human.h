#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "decorator.h"

class component;

class Human: public Decorator {
	public:
		Human( Component *component );
		string play(vector<Card> hand, Board board) override;
};

#endif
