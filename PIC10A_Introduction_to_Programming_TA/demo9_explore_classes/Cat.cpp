#include "Cat.h"
// default constructor
Cat::Cat() {
	age = 0;
	setBreed("American Shorthair"); // default breed
}

// Cat::Cat(std::string breed_in) {
// 	setBreed(breed_in);
// }

void Cat::setBreed(std::string breed_in) {
	breed = breed_in;
}

// std::string Cat::talk() const {
std::string Cat::talk(int number) {
	age = age + number;
	return "meow";
}

int Cat::getAge(){
	return age;
}

std::string Cat::getBreed(){
	return breed;
}
