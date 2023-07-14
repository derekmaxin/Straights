#include <iostream>

#include "board.h"

using namespace std;

//helper
int numericalRank(string rank){
	if (rank == "A") return 1;
	if (rank == "2") return 2;
	if (rank == "3") return 3;
	if (rank == "4") return 4;
	if (rank == "5") return 5;
	if (rank == "6") return 6;
	if (rank == "7") return 7;
	if (rank == "8") return 8;
	if (rank == "9") return 9;
	if (rank == "T") return 10;
	if (rank == "J") return 11;
	if (rank == "Q") return 12;
	if (rank == "K") return 13;
	return 0; //should never happen
}


//returns true if the passed card is sucessfully played (according to the rules); false otherwise
bool Board::playCard(Card card){
	string rank = card.getRank();
	string suite = card.getSuite();
	int nrank = numericalRank(rank);

	if (suite == "S"){
		if (this->spades.empty()){
			if (nrank == 7){
				//playing a new suite with a 7
				this->spades.push_back(card);
				return true;
			} else {
				//attempting to play a new suite not with a 7
				return false;
			}
		} else if (nrank > 7){
			if (nrank == numericalRank(this->spades.back().getRank()) + 1){
				//rank is one more than the previous highest card in this suite, making it valid
				this->spades.push_back(card);
				return true;
			} else {
				return false;
			}
		} else if (nrank < 7){
			if (nrank == (numericalRank(this->spades.front().getRank()) - 1)){
				//rank is one less than the previous lowest card in this suite, making it valid
				this->spades.insert(this->spades.begin(), card);
				return true;
			} else {
				return false;
			}
		}
	} else if (suite == "C"){
		if (this->clubs.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                this->clubs.push_back(card);
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numericalRank(this->clubs.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                this->clubs.push_back(card);
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numericalRank(this->clubs.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                this->clubs.insert(this->clubs.begin(), card);
                                return true;
                        } else {
                                return false;
                        }
                }
	} else if (suite == "H"){
		if (this->hearts.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                this->hearts.push_back(card);
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numericalRank(this->hearts.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                this->hearts.push_back(card);
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numericalRank(this->hearts.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                this->hearts.insert(this->hearts.begin(), card);
                                return true;
                        } else {
                                return false;
                        }
                }
	} else if (suite == "D"){
		if (this->diamonds.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                this->diamonds.push_back(card);
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numericalRank(this->diamonds.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                this->diamonds.push_back(card);
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numericalRank(this->diamonds.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                this->diamonds.insert(this->diamonds.begin(), card);
                                return true;
                        } else {
                                return false;
                        }
                }
	}
	return false; //invalid card; should never happen
}
