//
//  CreateDeck.cpp
//  demo14_shuffle_cards
//
//  Created by KoraJr on 5/15/17.
//  Copyright © 2017 Ucla-Mathematics. All rights reserved.
//

#include "CreateDeck.hpp"

//std::vector<Card> createDeck(size_t numOfDeck){
//    std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};
//    std::vector<std::string> faces = {"A"};
//    for (size_t faceIndex = 2; faceIndex <= 10; ++faceIndex){
//        faces.push_back(std::to_string(faceIndex));
//    }
//    faces.push_back("J");
//    faces.push_back("Q");
//    faces.push_back("K");
//    // std::vector<std::string> figures = {"J", "Q", "K"};
//    //faces.insert(faces.end(), figures.begin(), figures.end());
//    
//    
//    std::vector<Card> deck;
//    deck.reserve(numOfDeck * 52); // for performance purpose!
//    
//    for (size_t deckIndex = 0; deckIndex < numOfDeck; ++deckIndex){
//        for (size_t suitIndex = 0; suitIndex < suits.size(); ++suitIndex){
//            for (size_t faceIndex = 0; faceIndex < faces.size(); ++ faceIndex){
//                deck.push_back(Card(suits[suitIndex], faces[faceIndex]));
//            }
//        }
//    }
//    
//    return deck;
//}

void createDeck(std::vector<Card>& deck, size_t numOfDeck) {
        std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};
        std::vector<std::string> faces = {"A"};
        for (size_t faceIndex = 2; faceIndex <= 10; ++faceIndex){
            faces.push_back(std::to_string(faceIndex));
        }
        faces.push_back("J");
        faces.push_back("Q");
        faces.push_back("K");
        // std::vector<std::string> figures = {"J", "Q", "K"};
        //faces.insert(faces.end(), figures.begin(), figures.end());

    // deck.clear();
    for (size_t cleanIndex = 0; cleanIndex < deck.size(); ++cleanIndex){
        deck.pop_back();
    }
    
    deck.reserve(numOfDeck * 52); // for performance purpose!
    
        for (size_t deckIndex = 0; deckIndex < numOfDeck; ++deckIndex){
            for (size_t suitIndex = 0; suitIndex < suits.size(); ++suitIndex){
                for (size_t faceIndex = 0; faceIndex < faces.size(); ++ faceIndex){
                    deck.push_back(Card(suits[suitIndex], faces[faceIndex]));
                }
            }
        }
}
