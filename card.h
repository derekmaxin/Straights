#include <string>
#include <iostream>

using namespace std;

class Card {
	string rank; //1 2 3 4 5 6 7 8 9 10 J Q K
	string suite; //S C H D
	public:
	Card(std::string rank, std::string suite); //constructor

	string &getRank();
	string &getSuite();
};

std::ostream &operator<<(std::ostream &out, Card &card);
