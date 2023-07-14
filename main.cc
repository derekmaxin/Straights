#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>

//#include "card.h"
//#include "board.h"
#include "player.h"
#include "human.h"

//gameloop

using namespace std;

//helper
void printDeck(vector<Card> deck) {
	int j = 1;
	for (Card i : deck) {
		if (j % 13 == 0) {
			cout << i << endl;
	 	} else {
			cout << i << " ";
		}
		j++;
	}
}

//helper
string isWinner(int p1Score, int p2Score, int p3Score, int p4Score){
	int l1 = min(p1Score,p2Score);//add the possibility of mutliple winners later
	int l2 = min(p3Score,p4Score);
	int low = min(l1,l2);
	if (p1Score >= 80 || p2Score >= 80 || p3Score >= 80 || p4Score >= 80){
		if (p1Score == low){
			return "Player1";
		} else if (p2Score == low){
			return "Player2";
		} else if (p3Score == low){
			return "Player3";
		} else if (p4Score == low){
			return "Player4";
		}
	}
	return "none";
}

//helper
int calculateScore(vector<Card> cards){
	int score = 0;
	for ( Card i : cards){
		cout << i << " ";
		if (i.getRank() == "A") score += 1;
		if (i.getRank() == "2") score += 2;
		if (i.getRank() == "3") score += 3;
		if (i.getRank() == "4") score += 4;
		if (i.getRank() == "5") score += 5;
		if (i.getRank() == "6") score += 6;
		if (i.getRank() == "7") score += 7;
		if (i.getRank() == "8") score += 8;
		if (i.getRank() == "9") score += 9;
		if (i.getRank() == "T") score += 10;
		if (i.getRank() == "J") score += 11;
		if (i.getRank() == "Q") score += 12;
		if (i.getRank() == "K") score += 13;
	}
	return score;
}

int main(int argc, char *argv[]){
	//initialize game
	//cout << "arg: " << stoi(argv[1]) << endl;
	bool p1IsCom = false;
	bool p2IsCom = false;
	bool p3IsCom = false;
	bool p4IsCom = false;

	string cmd;

	cout << "Is player1 a human (h) or a computer (c)?" << endl;
	cin >> cmd;
	if (cmd == "c") p1IsCom = true;
	cout << "Is player2 a human (h) or a computer (c)?" << endl;
	cin >> cmd;
	if (cmd == "c") p2IsCom = true;
	cout << "Is player3 a human (h) or a computer (c)?" << endl;
	cin >> cmd;
	if (cmd == "c") p3IsCom = true;
	cout << "Is player4 a human (h) or a computer (c)?" << endl;
	cin >> cmd;
	if (cmd == "c") p4IsCom = true;

	
	//initialize players
	//scores will be updated after each round
	int p1Score = 0;
	int p2Score = 0;
	int p3Score = 0;
	int p4Score = 0;

	//initialize deck
	vector<Card> deck = {
		{"A","C"},{"2","C"},{"3","C"},{"4","C"},{"5","C"},{"6","C"},{"7","C"},{"8","C"},{"9","C"},{"T","C"},{"J","C"},{"Q","C"},{"K","C"},
		{"A","D"},{"2","D"},{"3","D"},{"4","D"},{"5","D"},{"6","D"},{"7","D"},{"8","D"},{"9","D"},{"T","D"},{"J","D"},{"Q","D"},{"K","D"},
		{"A","H"},{"2","H"},{"3","H"},{"4","H"},{"5","H"},{"6","H"},{"7","H"},{"8","H"},{"9","H"},{"T","H"},{"J","H"},{"Q","H"},{"K","H"},
   		{"A","S"},{"2","S"},{"3","S"},{"4","S"},{"5","S"},{"6","S"},{"7","S"},{"8","S"},{"9","S"},{"T","S"},{"J","S"},{"Q","S"},{"K","S"}		
	
	};
	
	int round = 0; //keeps track of which round we are on

	//gameloop
	while (isWinner(p1Score,p2Score,p3Score,p4Score) == "none"){
	
	//shuffle

	unsigned seed = stoi(argv[1]); //std::chrono::system_clock::now().time_since_epoch().count();

	for (int i = 0; i < 1000; i++){
		std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
	}

	vector<Card> hand1; //player 1's hand
	vector<Card> hand2; //player 2
	vector<Card> hand3; //player 3
	vector<Card> hand4; //player 4
	
	

	//deal
	int count = 0;
	int startingPlayer = 1;
	for ( Card i : deck ) {
		if (count < 13){
			if (i.getRank() == "7" && i.getSuite() == "S") startingPlayer = 1;
			hand1.push_back(i);
		} else if (count < 26){
			if (i.getRank() == "7" && i.getSuite() == "S") startingPlayer = 2;
			hand2.push_back(i);
		}else if (count < 39){
			if (i.getRank() == "7" && i.getSuite() == "S") startingPlayer = 3;
			hand3.push_back(i);
		}else{
			if (i.getRank() == "7" && i.getSuite() == "S") startingPlayer = 4;
			hand4.push_back(i);
		}
		count++;
	}
	
	//start round
	cout << "A new round begins. It's Player" << startingPlayer << "'s turn to play." << endl; 
	
	
	//inner game loop (playing all the cards on the board in a given round)
		
	Board board;
	Component *player1 = new Player(hand1,board);
	if (!(p1IsCom)){
		player1 = new Human(player1); //decorate as human
	}
	Component *player2 = new Player(hand1,board);
	if (!(p2IsCom)){
		player2 = new Human(player2); //decorate as humam
	}
	Component *player3 = new Player(hand1,board);
        if (!(p3IsCom)){
                player3 = new Human(player3); //decorate as human
        }
	Component *player4 = new Player(hand1,board);
        if (!(p4IsCom)){
                player4 = new Human(player4); //decorate as human
        }
	
	//each player's discards for this round;
	vector<Card> p1Discards;
	vector<Card> p2Discards;
	vector<Card> p3Discards;
	vector<Card> p4Discards;

	int turn = 0; //used to calculate who's turn it is and it it's the first turn
	string s;
	for (int i = 0; i < 52; i++){ // 52 cards to be played each round
	
		if (((startingPlayer + turn) % 4) == 1) { //player1's turn
			s = player1->play(hand1, board);
			string cmd = string(1,s.back());
			if (cmd == "p"){ //play
				Card c {s.substr(0,1),s.substr(1,1)};
				board.playCard(c);
				//remove played card from hand
				int j = 0;
				for (Card i : hand1){
					if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
						hand1.erase(hand1.begin() + j);
					}
					j++;
				}
				cout << "Player1 plays " << c << endl;
				//cout << s.substr(0,1) << " " << s.substr(1,1) << endl;
				//cout << "c: " << c << endl;
			} else if (cmd == "d"){ //discard
				Card c {s.substr(0,1),s.substr(1,1)};
				//remove played card from hand
                                int j = 0;
                                for (Card i : hand1){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand1.erase(hand1.begin() + j);
                                        }
                                        j++;
                                }
				cout << "Player1 discards " << c << endl;
				p1Discards.push_back(c);
			} else if (s == "deck"){
				printDeck(deck);
				turn--;
			} else if (s == "quit"){
				return 0;
			} else if (s == "ragequit"){
				p1IsCom = true;
				delete player1;
				player1 = new Player(hand1,board);
				cout << "Player1 ragequits. A computer will now take over." << endl;
				turn--; //check do i need this
			}
		//	cout << "1" << endl;	
		} else if (((startingPlayer + turn) % 4) == 2){ //player2's
			s = player2->play(hand2, board);
                        string cmd = string(1,s.back());
                        if (cmd == "p"){ //play
                                Card c {s.substr(0,1),s.substr(1,1)};
                                board.playCard(c);
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand2){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand2.erase(hand2.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player2 plays " << c << endl;
                        } else if (cmd == "d"){ //discard
                                Card c {s.substr(0,1),s.substr(1,1)};
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand2){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand2.erase(hand2.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player2 discards " << c << endl;
                                p2Discards.push_back(c);
                        } else if (s == "deck"){
                                printDeck(deck);
				turn--;
                        } else if (s == "quit"){
                                return 0;
                        } else if (s == "ragequit"){
                                p2IsCom = true;
				delete player2;
                                player2 = new Player(hand2,board);
                                cout << "Player2 ragequits. A computer will now take over." << endl;
                                turn--; //check do i need this
                        }
		//	cout << "2" << endl;
		} else if (((startingPlayer + turn) % 4) == 3){ //player3's
			s = player3->play(hand3, board);
                        string cmd = string(1,s.back());
                        if (cmd == "p"){ //play
                                Card c {s.substr(0,1),s.substr(1,1)};
                                board.playCard(c);
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand3){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand3.erase(hand3.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player3 plays " << c << endl;
                        } else if (cmd == "d"){ //discard
                                Card c {s.substr(0,1),s.substr(1,1)};
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand3){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand3.erase(hand3.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player3 discards " << c << endl;
                                p3Discards.push_back(c);
                        } else if (s == "deck"){
                                printDeck(deck);
				turn--;
                        } else if (s == "quit"){
                                return 0;
                        } else if (s == "ragequit"){
                                p3IsCom = true;
				delete player3;
                                player3 = new Player(hand3,board);
                                cout << "Player3 ragequits. A computer will now take over." << endl;
                                turn--; //check do i need this
                        }
		//	cout << "3" << endl;
		} else if (((startingPlayer + turn) % 4) == 0){ //player4's
			s = player4->play(hand4, board);
                        string cmd = string(1,s.back());
                        if (cmd == "p"){ //play
                                Card c {s.substr(0,1),s.substr(1,1)};
                                board.playCard(c);
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand4){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand4.erase(hand4.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player4 plays " << c << endl;
                        } else if (cmd == "d"){ //discard
                                Card c {s.substr(0,1),s.substr(1,1)};
                                //remove played card from hand
                                int j = 0;
                                for (Card i : hand4){
                                        if (i.getRank() == s.substr(0,1) && i.getSuite() == s.substr(1,1)){
                                                hand4.erase(hand4.begin() + j);
                                        }
                                        j++;
                                }
                                cout << "Player4 discards " << c << endl;
                                p4Discards.push_back(c);
                        } else if (s == "deck"){
                                printDeck(deck);
				turn--;
                        } else if (s == "quit"){
                                return 0;
                        } else if (s == "ragequit"){
                                p4IsCom = true;
				delete player4;
                                player4 = new Player(hand4,board);
                                cout << "Player4 ragequits. A computer will now take over." << endl;
                                turn--; //check do i need this
                        }
		//	cout << "4" << endl;
		}
		turn++;
	}//end of inner game loop

	//print out discards and scores for this round
	cout << "Player1's discards: ";
	int p1ThisRound = calculateScore(p1Discards);
	cout << endl << "Player1's score: " << p1Score << " + " << p1ThisRound << " = " << (p1Score + p1ThisRound) << endl;
	cout << "Player2's discards: ";
	int p2ThisRound = calculateScore(p2Discards);
	cout << endl << "Player2's score: " << p2Score << " + " << p2ThisRound << " = " << (p2Score + p2ThisRound) << endl;
	cout << "Player3's discards: ";
	int p3ThisRound = calculateScore(p3Discards);
	cout << endl << "Player3's score: " << p3Score << " + " << p3ThisRound << " = " << (p3Score + p3ThisRound) << endl;
	cout << "Player4's discards: ";
	int p4ThisRound = calculateScore(p4Discards);
	cout << endl << "Player4's score: " << p4Score << " + " << p4ThisRound << " = " << (p4Score + p4ThisRound) << endl;	
	
	//update scores
	p1Score += p1ThisRound;
	p2Score += p2ThisRound;
	p3Score += p3ThisRound;
	p4Score += p4ThisRound;
	
	delete player1;
	delete player2;
	delete player3;
	delete player4;

	//break; //temp - break outer loop for testing
	round++;
	}//end of game loop

	cout << isWinner(p1Score,p2Score,p3Score,p4Score) << " wins!" << endl;
}
