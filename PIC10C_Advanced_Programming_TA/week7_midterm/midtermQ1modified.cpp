#include <iostream>

class Algo {       // Algo = Something in Spanish
    private:
        int theData;
        int& refData;
    public:
        Algo(int data) : theData(data), refData(theData) { }
        Algo( const Algo& b ) : theData(b.theData), refData(theData) {}
        Algo& operator=( const Algo& rhs ) = default;
        ~Algo() {}
};

int main() {
    {
        Algo thing1(3);
        Algo thing2 = Algo(3);
        thing2 = Algo(2);
    }
    std::cout << "Help! I want to see the light!!!\n";
    return 0; 
}
