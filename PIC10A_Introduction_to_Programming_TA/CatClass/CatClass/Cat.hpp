#ifndef __CAT__
#define __CAT__
#include<string>
class Cat {
public:
    std::string breed;
    
    /** Default constructor */
    Cat();
    
    /** another constructor
     @param breen_in assigns the breed of the cat
     */
    Cat(std::string breed_in);
    // Cat(std::string breed_in) const;
    // Cat(std::string& breed_in);
    
    /** function that returns cat meow
     @return the string "meow"
     */
    std::string talk() const;
    // std::string talk();
    
    // private:
    /** function that sets the breed
     * @param breed_in
     */
    void setBreed(std::string breed_in);
    // void setBreed(std::string& breed_in);
    // void setBreed(std::string breed_in) const;
};
#endif
