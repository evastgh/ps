//
//  CreateDeck.hpp
//  demo14_shuffle_cards
//
//  Created by KoraJr on 5/15/17.
//  Copyright © 2017 Ucla-Mathematics. All rights reserved.
//

#ifndef CreateDeck_hpp
#define CreateDeck_hpp

#include <stdio.h>
#include <vector>
#include "Card.h"

// std::vector<Card> createDeck(size_t numOfDeck = 1);
void createDeck(std::vector<Card>& deck, size_t numOfDeck = 1);

#endif /* CreateDeck_hpp */
