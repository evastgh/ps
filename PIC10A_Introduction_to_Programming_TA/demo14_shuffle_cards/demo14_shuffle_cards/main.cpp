//
//  main.cpp
//  demo14_shuffle_cards
//
//  Created by KoraJr on 5/15/17.
//  Copyright © 2017 Ucla-Mathematics. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include "Card.h"
#include "CreateDeck.hpp"

using namespace std;

void printDeck(vector<Card>& deckToBePrinted);
void shuffleDeck(vector<Card>& deckToBeShuffled, size_t shuffleTimes);

int main(int argc, const char * argv[]) {
    
    std::vector<Card> deck;
    createDeck(deck);
    // printDeck(deck);
    // cout << endl;
    shuffleDeck(deck, 100);
    // printDeck(deck);
    
    return 0;
}

void printDeck(vector<Card>& deckToBePrinted){
    size_t deckSize = deckToBePrinted.size();
    for (size_t cardIndex = 0; cardIndex < deckSize; ++cardIndex){
        cout << deckToBePrinted[cardIndex].card_as_string();
    }
    cout << "===" << endl;
}

void shuffleDeck(vector<Card>& deckToBeShuffled, size_t shuffleTimes){
    srand(static_cast<uint>(time(nullptr)));
    
    size_t deckSize = deckToBeShuffled.size();
    printDeck(deckToBeShuffled);
    for (size_t shuffleIndex = 0; shuffleIndex < shuffleTimes; ++shuffleIndex){
        size_t shufflePlace = rand() % deckSize;
        
        vector<Card> topHalfDeck;
        topHalfDeck.reserve(shufflePlace);
        // topHalfDeck.assign(deckToBeShuffled.begin(), deckToBeShuffled.begin() + shufflePlace);
        for (size_t assignIdx = 0; assignIdx < shufflePlace; ++assignIdx){
            // topHalfDeck[assignIdx] = deckToBeShuffled[assignIdx];
            topHalfDeck.push_back(deckToBeShuffled[assignIdx]);
        }
        
        vector<Card> lowerHalfDeck;
        lowerHalfDeck.assign(deckToBeShuffled.begin()+shufflePlace, deckToBeShuffled.end());
        
        deckToBeShuffled.clear();
        
        // deckToBeShuffled.insert(deckToBeShuffled.end(), topHalfDeck.begin(), topHalfDeck.end());
        for (size_t insertIdx = 0; insertIdx < topHalfDeck.size() && insertIdx < lowerHalfDeck.size(); ++insertIdx){
            deckToBeShuffled.push_back(topHalfDeck[insertIdx]);
            deckToBeShuffled.push_back(lowerHalfDeck[insertIdx]);
        }
        if (topHalfDeck.size() > lowerHalfDeck.size()){
            for (size_t insertIdx = lowerHalfDeck.size(); insertIdx < topHalfDeck.size(); ++insertIdx){
                deckToBeShuffled.push_back(topHalfDeck[insertIdx]);
            }
        }
        else if (lowerHalfDeck.size() > topHalfDeck.size()){
            for (size_t insertIdx = topHalfDeck.size(); insertIdx < lowerHalfDeck.size(); ++insertIdx){
                deckToBeShuffled.push_back(lowerHalfDeck[insertIdx]);
            }
        }
        
        printDeck(deckToBeShuffled);
    }
}
