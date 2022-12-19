/*******************************************************************
** Program: TwentyOne
** Author: Your Name
** Date: 11/20/2022
** Description: Create a game called TwentyOne, which is similar to the Blackjack and War card games. This game has a dealer/computer and 1-4 players, and the game will generate random numbers from 1 to 11 to simulate the values in cards. All players start with a specified amount of money, which they determine at the start of the game, and the goal is to see if you can get closer than the dealer to twenty-one points without going over (bust).
** Input:
• Number of decks (1/2/4; default: 1), 
• Choose action (n/r/q; default: n) (n: new round, r: show rules, q: quit)
• Choose play (h/s/r/q; default: h) (h: hit, s: stand, r: show rules, q: quit).
** Output:
• Game banner
• Question: How many decks to be used
• Total chips for player to bet 
• Question: Next step: (start a new round, show the rules, or quit)
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

// Error exceptions.
struct BadSuit {};
struct BadNumberDecks {};

// Global constants.
const int PLAYER_CHIP = 100;
const int DEALER_CHIP = 10000;
const int MAX_BET = 21;
const int MAX_CHARACTER = 1000;


// Class card
class Card {
	public:

		Card(int num1 = 1, char suit1 = 's') {
			if (num1 < 1) num = 1;
			else if (num1 > 13) num = 13;
			else num=num1 ;
			if (suit1 == 'c' || suit1 == 'C') suit = 'c';
			else if (suit1 == 's' || suit1 == 'S') suit = 's';
			else if (suit1 == 'h' || suit1 == 'H') suit = 'h';
			else if (suit1 == 'd' || suit1 == 'D') suit = 'd';
			else throw BadSuit();
		}
		
		int getValue() const {
			return num;
		}

		std::string getRank() const {
			if (num == 1) return "A";
			else if (num == 2) return "2";
			else if (num == 3) return "3";
			else if (num == 4) return "4";
			else if (num == 5) return "5";
			else if (num == 6) return "6";
			else if (num == 7) return "7";
			else if (num == 8) return "8";
			else if (num == 9) return "9";
			else if (num == 10) return "10";
			else if (num == 11) return "J";
			else if (num == 12) return "Q";
			else if (num == 13) return "K";
		}
		
		char getSuit() const {
			return suit;
		}
		
	private:
		int num;
		char suit;
};		

std::ostream & operator<<(std::ostream &s, const Card &c) {
	return s << c.getRank() << "(" << c.getSuit() << ')';
}

// Class decks	
class Decks {
	public:
		Decks(int nDeck = 1): cards(), current(0) {
			// Create cards.
			create(nDeck); 	
		}

		void create(int nDeck) {
			if (nDeck != 1 && nDeck != 2 && nDeck != 4) 
				throw BadNumberDecks();
			cards.resize(nDeck*52);
			int index = 0;
			for (int i = 0; i < nDeck; i++)
				for (int n = 1; n <= 13; n++) { 
					cards[index++] = Card(n, 'c');
					cards[index++] = Card(n, 's');
					cards[index++] = Card(n, 'h');
					cards[index++] = Card(n, 'd');
				}
		}
		
		// Randomly shuffle cards
		void shuffle() {
			std::random_shuffle(cards.begin(), cards.end()); 
			current = 0;
		}
		
		// Deal card
		Card deal() {
			if (current == cards.size()) shuffle();
			return cards[current++];
		}

		void print() const {
			for (int i = 0; i < cards.size(); i++) 
				cout << cards[i] << endl;
		}
		
	private:
		std::vector<Card> cards;
		int current;
};

// Class hand, for player or dealer
class Hand {
	public:
		// Constructor.
		Hand(): cardsAtHand() {}
		
		// Add card to hand
		void addCard(Card card) {
			cardsAtHand.push_back(card);
		}

		int getValue() const {
			int value = 0;
			bool ifAce = false;  
			for (int i = 0; i < cardsAtHand.size(); i++) {
				int cardValue = cardsAtHand[i].getValue();
				if (cardValue > 10) cardValue = 10; 	
				if (cardValue == 1) ifAce=true;
				value += cardValue;
			}

			if (ifAce && value < 12) value += 10;	
			return value;
		}

		int size() const {
			return cardsAtHand.size();
		}

		bool blackjack() const {
			return (cardsAtHand.size() == 2 && getValue() == 21);
		}
		
		void removeAllCards() {
			cardsAtHand.clear();
		}
		
		void print(bool hideFirst=false) const {
			if (cardsAtHand.size() == 0) 
				std::cout << "No card." << std::endl;
			for (int i = 0; i < cardsAtHand.size(); i++) 
				if (i == 0 && hideFirst) cout << "?(?) ";
				else cout << cardsAtHand[i] << ' ';
			cout << endl;
		}
		
	private:
		std::vector<Card> cardsAtHand;
}; 

// Class game
class Game {
	public:
		// Constructor.
		Game(): myDecks(), playerHand(), dealerHand() {
			nPlayerChip = PLAYER_CHIP;
			nDealerChip = DEALER_CHIP;
		}

		// Game play
		void play() {
			std::srand(std::time(NULL)); 
			char input = beginGame();
			while (input == 'n') {
				beginRound();
				do {
					input = inRound();
				} while (input == 'h');
				input = endRound(input);
			}
			endGame();
		}

	private:

		char beginGame() {
			cout << "###########################" << endl;
			cout << "#        TwentyOne        #" << endl;
			cout << "###########################" << endl;
			cout << endl;

			int nDeck;
			do {
				cout << "Choose the number of decks to use ";
				cout << "[1/2/4] (default: 1):  ";
				cin.getline(temp, MAX_CHARACTER);
				nDeck = firstChar(temp, MAX_CHARACTER) - '0';

				if (nDeck == 0) nDeck = 1; 
			} while (nDeck != 1 && nDeck != 2 && nDeck != 4);
			cout << endl;

			myDecks.create(nDeck);
			cout << nDeck << " deck" << (nDeck == 1 ? "" : "s");
			cout << " (" << 52 * nDeck << " cards) ";
			cout << (nDeck == 1 ? "has" : "have");
			cout << " been created and shuffled." << endl;
			cout << "You have " << PLAYER_CHIP << " chips.";
			cout << "You can bet upto " << MAX_BET << " chips for each round.\n" << endl;
			
			// User input
			char input; 
			do {
				cout << "Type n for a new round, r for rules, and q to quit [n/r/q] (default: n): ";
				cin.getline(temp, MAX_CHARACTER);
				input = firstChar(temp, MAX_CHARACTER); 
				if (input == '0') input = 'n';
				if (input == 'r') displayRules();
			} while (input != 'n' && input != 'q');
			cout << endl;
			return input;
		}

		// Beginning round
		void beginRound() {
			cout << "===================================" << endl;
			cout << "* Starting a New Round (your chips: ";
			cout << nPlayerChip << ").\n" << endl;

			bool insufficient = false; 
			do {
				if (insufficient) {
					cout << "You only have " << nPlayerChip;
					cout << " chip(s)." << endl; 
				};
				cout << "How much do you bet you can beat the dealer? ";
				cout << "[1-21] (default: 1): ";
				insufficient = false;

				cin.getline(temp, MAX_CHARACTER); 
				nBet = firstChar(temp, MAX_CHARACTER) - '0';
				if (nBet == 0) nBet = 1;
				if (nBet > nPlayerChip || nBet > nDealerChip) 
					insufficient = true;
			} while (nBet < 1 || nBet > MAX_BET || insufficient);
			cout << "You bet " << nBet << " chips";
			cout << (nBet == 1 ? "." : "s.") << endl;

			dealerHand.removeAllCards();
			playerHand.removeAllCards();
			myDecks.shuffle();

			dealerHand.addCard(myDecks.deal());
			playerHand.addCard(myDecks.deal());
			dealerHand.addCard(myDecks.deal());
			playerHand.addCard(myDecks.deal());
		}

		char inRound() {
			int playerValue = playerHand.getValue();
			if (playerHand.blackjack()) {
				cout << "You got the blackjack!" << endl;
				return 'j'; 
			};

			if (playerValue > 21) return 'b'; 

			showHands(true);	

			char input;
			do {
				cout << "Type h for Hit, s for Stand, r for rules, q to quit [h/s/r/q] (default: h): ";
				cin.getline(temp, MAX_CHARACTER);
				input = firstChar(temp, MAX_CHARACTER);
				if (input == '0') input = 'h'; 
				if (input == 'r') displayRules();
			} while (input != 'h' && input != 's' && input != 'q');

			if (input == 'h') playerHand.addCard(myDecks.deal()); 
			return input;
		}

		char endRound(char in) {
			int playerValue = playerHand.getValue();
			if (in == 'b') {
				cout << "\nYou have:\t "; 
				playerHand.print();
				cout << "The dealer has " << dealerHand.getValue() << " points. You lose ";
				cout << nBet << " chips!" << endl;
				takeChips(-nBet);
			}
			else if (in == 'q') {
				cout << "\nYou lost " << nBet << " chips!";
				cout << endl;
				takeChips(-nBet);
				return in;
			}
			else if (in == 'j') {
				showHands();
				if (dealerHand.blackjack()) {
					cout << "The dealer has " << dealerHand.getValue() << " points. Tie game! " << endl;
				}
				else {
					cout << "You got " << playerHand.getValue() << " in hand. You win! ";
					takeChips(nBet);
				};
			}
			else {
				while (dealerHand.getValue() < 17) 
					dealerHand.addCard(myDecks.deal());
				showHands();

				int dealerValue = dealerHand.getValue();
				// Dealer busted
				if (dealerValue > 21) { 
					cout << "The dealer busts! You win! You ";
					cout << "gained " << nBet;
					cout << " chips." << endl;
					takeChips(nBet);
				}
				// Dealer wins
				else if (dealerValue > playerValue) {
					if (dealerHand.blackjack()) {
						cout << "Dealer got the blackjack!\n";
					}
					cout << "The dealer has " << dealerHand.getValue() << " points. You lose " << nBet << " chips!" << endl;
					takeChips(-nBet);
				} 
				// Player wins
				else if (dealerValue < playerValue) {
					cout << "You got " << playerHand.getValue() << " in hand. You win " << nBet << " chips!" << endl;
					takeChips(nBet);
				}
				// Tied
				else { 
					if (dealerHand.blackjack()) {
						cout << "Dealer got the ";
						cout << "blackjack! ";
						cout << "You lost " << nBet;
						cout << " chips." << endl;
						takeChips(-nBet);
					}

					else {	
						cout << "It is tied, and the ";
						cout << "bet is returned.";
						cout << endl;
					}
				};

			}
			cout << "\n* End of the Round (your chips: ";
			cout << nPlayerChip << ")." << endl;
			cout << "===================================" << endl;
		
			if (nPlayerChip == 0 || nDealerChip == 0) return 'q'; 

			char input;
			do {
				cout << "\nType n for a new round, r for rules, q to quit [n/r/q] (default: n): ";
				cin.getline(temp, MAX_CHARACTER);
				input = firstChar(temp, MAX_CHARACTER);
				if (input == '0') input = 'n'; 
				if (input == 'r') displayRules();
			} while (input != 'n' && input != 'q');
			return input;
		}

		void endGame() {
			cout << "\nYour remaining chips: " << nPlayerChip;
			cout << " (you ";
			int diff = nPlayerChip - PLAYER_CHIP;
			if (diff > 0) cout << "gained " << diff << " chips).";
			else if (diff < 0) 
				cout << "lost " << -diff << " chips).";
			else cout << "have the same number of chips as started).";
			cout << endl << endl;
			cout << "###########################" << endl;
			cout << "#     End of the Game     #" << endl;
			cout << "###########################" << endl;
		}

		// Display rules.
		void displayRules() {
			cout << endl;
			cout << "===================================" << endl;
			cout << "# How to play the TwentyOne game " << endl;
			cout << "\n\tIf the player busts (goes over 21), the player automatically loses their bet, and the dealer doesn’t need to play against that player" << endl;
			cout << "\n\tIf the player gets exactly 21 in hand, the player automatically wins their bet, and the dealer doesn’t need to play" << endl;
			cout << "\n\tIf the dealer busts (goes over 21), the player automatically wins their bet." << endl;
			cout << "\n\tIf the dealer ties with the player, then the player doesn’t win or lose their bet." << endl;
			cout << "\n\tIf the player’s bet is more than their bank, then you need to continue to re-prompt for a new bet until a good value is given." << endl;
			cout << "\n\tIf a player’s bank is 0, they get skipped." << endl;
			cout << "\n\tIf all players’ banks are 0, then the game is automatically over!" << endl;
			cout << "\n\tAfter all players take a turn against the dealer, then the players can collectively cash out or play again." << endl;
			cout << "===================================" << endl;
			cout << endl;
		}

		static char firstChar(char *temp, int size) {
			int i=0;
			while (i < size && temp[i] != '\0' && (temp[i] == ' '\
				|| temp[i] == '\t' || temp[i] == '\n'))
				i++;
			if (temp[i] == '\0' || i >= size) return '0';
			else return temp[i];
		}
		
		void showHands(bool hideFirst = false) {
			cout << "\nDealer has:\t ";
			dealerHand.print(hideFirst);
			cout << "You have:\t ";
			playerHand.print(); 
			cout << endl;
		}

		void takeChips(int amount) {
			nPlayerChip += amount;
			nDealerChip -= amount;
		}

	private:
		Decks myDecks;
		Hand playerHand, dealerHand;
		int nPlayerChip, nDealerChip;
		int nBet;

		char temp[MAX_CHARACTER+1];
};

// Driver
int main() {
	Game g;
	try {
		g.play();
	}
	catch(BadSuit e) {
		std::cerr << "*** Bad card suit is given.\n";
		std::exit(1);
	}
	catch(BadNumberDecks e) {
		std::cerr << "*** Bad number of decks is given.\n";
		std::exit(1);
	};
	return 0;
}
