#include "Cat.h"
// default constructor
Cat::Cat() { }

void Cat::setBreed(std::string breed_in) {
	breed = breed_in;
}
std::string Cat::talk() const {
	return "meow";
}
