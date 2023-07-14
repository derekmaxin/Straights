#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <vector>
//#include "card.h"
#include "board.h"

class Component{
	public:
		virtual string play(vector<Card> hand, Board board) = 0;
		virtual ~Component();

};

#endif
