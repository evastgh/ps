#include<string>
#include<stdexcept>
#include<sstream>
#include "Card.h"

/* Definitions of Card constructor and member function */

// Card constructor: sets the suit and face based on the inputs
Card::Card(const std::string &suitType, const std::string &face) : suit(suitType), face(face) {}

// Concatenates the face with the suit in square brackets, returning the result
std::string Card::card_as_string() const { return face + "[" + suit + "]"; }


/* Other functions */

std::string num_to_string(std::size_t n)
{
	// Create a string stream to hold n
	std::ostringstream o;

	// Push the number into the stream and return the string value
	o << n;
	return o.str();
}

int char_to_num(char c)
{
	// check the char is in a valid range and if not, throw an exception
	if (c < '0' || c > '9') // only valid if digit from 0-9 inclusive
		throw std::runtime_error("Invalid input to char_to_num");

	// value is char value minus 0 char value
	return static_cast<int>(c - '0');
}