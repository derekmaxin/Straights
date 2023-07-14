#include <iostream>
#include <string>

#include "human.h"
#include "component.h"

using namespace std;

Human::Human( Component *component ) : Decorator{component} {}

int numRank(string rank){
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
bool testLegal(Card card, Board board){
	string rank = card.getRank();
        string suite = card.getSuite();
        int nrank = numRank(rank);

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
                        if (nrank == numRank(board.spades.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numRank(board.spades.front().getRank()) - 1)){
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
                        if (nrank == numRank(board.clubs.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numRank(board.clubs.front().getRank()) - 1)){
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
                        if (nrank == numRank(board.hearts.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numRank(board.hearts.front().getRank()) - 1)){
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
                        if (nrank == numRank(board.diamonds.back().getRank()) + 1){
                                //rank is one more than the previous highest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                } else if (nrank < 7){
                        if (nrank == (numRank(board.diamonds.front().getRank()) - 1)){
                                //rank is one less than the previous lowest card in this suite, making it valid
                                return true;
                        } else {
                                return false;
                        }
                }
        }
        return false; //invalid card; should never happen	
}

//returns a string of 3 chars first two being rank and suite, third being p or d, for play or discard
string Human::play(vector<Card> hand, Board board){
	string s = component->play(hand, board);

	cout << "Cards on the table:" << endl << "Clubs: ";
	for ( Card i : board.clubs ) cout << i.getRank() << ' ';
	cout << endl << "Diamonds: ";
	for ( Card i : board.diamonds ) cout << i.getRank() << ' ';
	cout << endl << "Hearts: ";
        for ( Card i : board.hearts ) cout << i.getRank() << ' ';
	cout << endl << "Spades: ";
        for ( Card i : board.spades ) cout << i.getRank() << ' ';
	cout << endl << "Your hand: ";	
	for ( Card i : hand ) cout << i << ' ';

	
	vector<Card> legalPlays;
	
	//check for 7S
	bool firstPlay = false;
	for ( Card i : hand ){
		if (i.getRank() == "7" && i.getSuite() == "S"){
			firstPlay = true;
			legalPlays.push_back(i);
		}
	}
	
	if (!(firstPlay)){ 
		for ( Card i : hand ){
			if (testLegal(i, board)){
				legalPlays.push_back(i);	
			}
		}
	}
	cout << endl << "Legal plays: ";
	for ( Card i : legalPlays ) cout << i << ' ';
	cout << endl;
	
	string cmd;
	while (1){
		cin >> cmd;
		if (cmd == "play"){
			cin >> cmd;
			string r = string(1,cmd.front());
			string s = string(1,cmd.back());
			for ( Card i : legalPlays ) {
				if (r == i.getRank() && s == i.getSuite()){
					cmd.append("p");
					return cmd;
				}
			}
			cout << "This is not a legal play." << endl;
			continue;
		} else if (cmd == "discard"){
			cin >> cmd;
			if (legalPlays.empty()){
			      	cmd.append("d");
				return cmd;
			}
			cout << "You have a legal play. You may not discard" << endl;
			continue;
		} else if (cmd == "deck"){
			return "deck";
		} else if (cmd == "quit"){
			return "quit";
		} else if (cmd == "ragequit"){
			return "ragequit";
		}
		//break;
	}
	//cout << cmd;
	
	return s;
}
