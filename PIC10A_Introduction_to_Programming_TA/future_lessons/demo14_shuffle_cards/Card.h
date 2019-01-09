#ifndef __CARD__
#define __CARD__

#include<string>
#include<cstddef>

class Card{
public:
	/**
	Constructor: takes two inputs to create a Card object. The first input is a string, one of "Clubs", "Diamonds", "Hearts", or "Spades".
	The second input is the face as a string: "A" for Ace, "2", "3", ... "9", "10", "J" for Jack, "Q" for Queen, and "K" for King.

	@param suitType the suit, "Clubs", "Diamonds", "Hearts", or "Spades"
	@param face the face of the card, "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
	*/
	Card(const std::string &suitType, const std::string &face);

	/**
	This function returns the string representation of the card in the format "FACE[SUIT]". For example, "10[Diamonds]"

	@return the string representation of the card in the format described above
	*/
	std::string card_as_string() const;

private:
	std::string suit, face;

};


/**
Function num_to_string converts a size_t integer to a string.

For example,

string s = num_to_string(809);

sets s to "809"

@param n the size_t integer to convert to a string

@return the number as a string
*/
std::string num_to_string(std::size_t n);


/**
Function char_to_num converts a single numeric digit as a character to an int value.

For example, it is possible to set x to 1 by:

int x = char_to_num('1');

@param c the character, a digit 0-9 to be converte to an int

@return the int value of that digit
*/
int char_to_num(char c);


#endif