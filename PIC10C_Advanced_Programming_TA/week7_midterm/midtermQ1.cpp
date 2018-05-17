#include <iostream>

class Algo {       // Algo = Something in Spanish
    private:
        int* theData;
        size_t theSize;
        std::string name;
    public:
        explicit Algo(const std::string& name = "default", size_t n = 1) : theSize(n), name(name), theData( new int[n] ) { std::cout << "Algo constructor: name = " << name << " theData = " << theData << std::endl; }
        // read https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/explicit_keyword.htm
        /*explicit*/ Algo( const Algo& b ) : theSize( b.theSize ) , name(b.name + "_copy") {
            theData = new int[theSize];
            for ( size_t i = 0 ; i < theSize ; ++i )
                theData[i] = b.theData[i];
            std::cout << "Algo copy constructor: name = " << name << " theData = " << theData << std::endl; 
        }
        void saySomething() const { std::cout << "Algo saySomething: name = " << name << " theData = " << theData << std::endl; }
        // Algo& operator=( const Algo& rhs ) = delete;
        // Algo& operator=( const Algo& rhs ) {
        //     theSize = rhs.theSize;
        //     delete[] theData;
        //     theData = new int[theSize];
        //     for ( size_t i = 0 ; i < theSize ; ++i )
        //         theData[i] = rhs.theData[i];
        //     std::cout << "Algo assignment operator: theData = " << theData << std::endl; 
        //     return *this;
        // }
        ~Algo() { delete[] theData; }
};

int main() {
    {
        // Algo thing1(3);
        Algo thing2 = Algo("temporary", 10);
        thing2.saySomething();
        // thing2 = Algo();
        // thing2.saySomething();
    }
    std::cout << "Help! I want to see the light!!!\n";
    return 0; 
}
