#include "Cat.hpp"
// default constructor
Cat::Cat() {
    setBreed("American Shorthair"); // default breed
}

Cat::Cat(std::string breed_in) {
    setBreed(breed_in);
}

void Cat::setBreed(std::string breed_in) {
    breed = breed_in;
}

std::string Cat::talk() const {
    return "meow";
}
