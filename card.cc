#include "card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string rank, string suite): rank{rank}, suite{suite}{
}

string &Card::getRank(){
	return this->rank;
}

string &Card::getSuite(){
	return this->suite;
}

std::ostream &operator<<(std::ostream &out, Card &card){
	out << card.getRank() << card.getSuite();
	return out;
}
