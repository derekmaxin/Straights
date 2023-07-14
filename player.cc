#include "player.h"

Player::Player(vector<Card> hand, Board board) : score{0}, hand{hand}, board{board}, discard{vector<Card> {}}{
}

int numerRank(string rank){
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

//helper
bool testIfLegal(Card card, Board board){
        string rank = card.getRank();
        string suite = card.getSuite();
        int nrank = numerRank(rank);

        if (suite == "S"){
                if (board.spades.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numerRank(board.spades.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numerRank(board.spades.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                }
        } else if (suite == "C"){
                if (board.clubs.empty()){
if (nrank == 7){
                                //playing a new suite with a 7
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numerRank(board.clubs.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numerRank(board.clubs.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                }
        } else if (suite == "H"){
                if (board.hearts.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numerRank(board.hearts.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numerRank(board.hearts.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                }
        } else if (suite == "D"){
                if (board.diamonds.empty()){
                        if (nrank == 7){
                                //playing a new suite with a 7
                                return true;
                        } else {
                                //attempting to play a new suite not with a 7
                                return false;
                        }
                } else if (nrank > 7){
                        if (nrank == numerRank(board.diamonds.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
				return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numerRank(board.diamonds.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                }
        }
        return false; //invalid card; should never happen
}

//default computer behaviour
string Player::play(vector<Card> hand, Board board){
	string s;

	//check for 7S
	for ( Card i : hand ){
		if (i.getRank() == "7" && i.getSuite() == "S"){
			return "7Sp";
		}
	}

	for ( Card i : hand ){
		if (testIfLegal(i,board)){
			board.playCard(i);
			s = i.getRank() + i.getSuite() + "p"; //play
			//cout << "s " << s << endl;
			return s;
		}	
	}
	s = hand.front().getRank() + hand.front().getSuite() + "d"; //discard
	return s;
}

int Player::addToScore(int score){
}
