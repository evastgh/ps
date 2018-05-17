#include <iostream>
#include <memory>

class Algo {       // Algo = Something in Spanish
    private:
    std::shared_ptr<int> theData;
    // std::unique_ptr<int> theData;
        size_t theSize;
    public:
    Algo( size_t n = 1 ) : theSize(n), theData( new int[n] ) { }
        Algo( const Algo& b ) : theSize( b.theSize ), theData( new int[b.theSize] ) {
            for ( size_t i = 0 ; i < theSize ; ++i )
                theData.get()[i] = b.theData.get()[i];
        }
        Algo& operator=( const Algo& rhs ) = default;
        ~Algo() { }
};

int main() {
    {
        Algo thing1(3);
        Algo thing2 = Algo();
        thing2 = Algo();
    }
    std::cout << "Help! I want to see the light!!!\n";
    return 0; 
}
