#include <iostream>

class Thing;
class Cosa;

class Thing {
  public:
    // Default constuctor
    Thing() {}
    // Cosas are not implicit Things
    explicit Thing( const Cosa& ) {}
    // Translates Thing into Cosa. Note that the full signature is:
    //     Cosa Thing::operator()( const Thing& ) const;
    Cosa operator()( const Thing& t ) const;
};

// Cosa = Thing in Spanish
class Cosa {
  public:
    // Default constuctor
    Cosa() {}
    // Things are implicit Cosas
    Cosa( const Thing& ) {}
    // Translates Cosa into Thing. Note that the full signature is:
    //     Thing Cosa::operator()( const Cosa& ) const;
    Thing operator()( const Cosa& c ) const;
};
// Since Cosa is defined in terms of Thing, and vice versa, the code above does
// not compile the way it is presented. However, this can be fixed by first
// declaring, and then defining the member functions of these classes. I chose
// not to present the working version here in an effort to make the code more
// readable and [slightly?] less confusing.

Cosa Thing::operator()( const Thing& t ) const {
    return Cosa(t);
}
Thing Cosa::operator()( const Cosa& c ) const {
    return Thing(c);
}

template<typename FUN_T, typename THING_T>
void template_fun( const FUN_T& fun, const THING_T& t ){
  fun(t);
  return; 
}

int main(int argc, char** argv) {
    // /* part A */
    // Cosa c1;

    // /* part B */
    // Cosa c;
    // Cosa c2(c);

    // /* part C */
    // Cosa c;
    // auto mistery = c(c);
    
    // /* part D */
    // Thing t;
    // Cosa c;
    // auto mistery = c(t);

    // /* part E */
    // Thing t;
    // Cosa c;
    // auto mistery = t(c);
    
    /* Additional part */
    Thing t;
    Cosa c;
    template_fun(t, t);
    template_fun(t, c);
    template_fun(c, t);
    template_fun( c(t) , t );
    template_fun( Thing()( c(t) ) , c );
    template_fun( Cosa( c(c) ) , t(t) );

    return 0;
}
