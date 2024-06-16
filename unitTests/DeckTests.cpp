#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <sstream>
#include "Deck.h"
#include "ExplodingCard.h"
#include "pugixml.hpp"
#include "Player.h"
#include "Card.h"
#include "Game.hpp"

template <typename T>
bool isValueInList(const T& value, const std::vector<T>& list) {
    return std::ranges::find(list.begin(), list.end(), value) != list.end();
}

TEST(Deck, showSomeCards) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    auto cards = deck.showSomeCards(3);
    std::string expected = "Babybron\nBabysounours\nBabybel\n";
    std::string resultStr = "";
    for (auto c : cards) {
        resultStr += c->getName() + "\n";
    }
    EXPECT_EQ(resultStr, expected);
}

/**
* L'objectif était de tester la méthode shuffle de la classe Deck.
* Cependant, puisque nous avons déplacer la création des cartes dans le constructeur de la classe Deck,
* il n'est plus possible de tester la méthode shuffle sans modifier la classe Deck.
* Ou alors, il nous faudrait écrire les 20 ! combinaisons possibles de cartes dans le deck.
TEST(Deck, shuffle) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    deck.shuffle();
    std::vector<std::string> possibilities = { "Baby Boom\nDynamite\nTNT\n",
                                                "Baby Boom\nTNT\nDynamite\n",
                                                "Dynamite\nBaby Boom\nTNT\n",
                                                "Dynamite\nTNT\nBaby Boom\n",
                                                "TNT\nBaby Boom\nDynamite\n",
                                                "TNT\nDynamite\nBaby Boom\n" };

    EXPECT_TRUE(isValueInList(deck.dump(), possibilities));
}
*/

TEST(Deck, drawCard) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    //On vérifie que la carte tirée est bien la première de la liste
    auto drawC = deck.drawCard()->getName();
    std::string expected = "Babybron";
    EXPECT_EQ(drawC, expected);

    //On vérifie que la carte tirée précédemment n'est plus dans le deck
    //A savoir que l'on a également retiré les cartes "Baby Boom" et "Babysous" du deck
    //Pour pas que le joueur puisse les piocher au début de la partie 
    expected = R"(Babyg Brother
Babycyclette
Babytcoin
BabyShark
Babyfoot
Babybel
Babysounours
Babybron
BabyShark
Babyfoot
Babybel
Babysounours
Babybron
BabyShark
Babyfoot
Babybel
Babysounours
)";
    EXPECT_EQ(deck.dump(), expected);
}

TEST(Deck, addCardToRandom) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    const std::string xmlCard = R"(<?xml version = "1.0"?>
						   <root>
							<ExplodingCard name="Test"/>
						   </root>)";
    pugi::xml_document cardNode;
    pugi::xml_parse_result result2 = cardNode.load_string(xmlCard.c_str());
    ASSERT_TRUE(result2) << result2.description();
    pugi::xml_node cardRoot = cardNode.child("root");
    auto c = std::make_unique<ExplodingCard>(cardRoot.first_child(), eventCardManager);
    deck.addCardToRandom(move(c));

    std::vector<std::string> possibilities = {
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nTest\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nTest\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nTest\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nTest\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nTest\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nTest\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nTest\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nTest\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nTest\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nTest\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nTest\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nTest\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nTest\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nTest\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nTest\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nBabytcoin\nTest\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nBabycyclette\nTest\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Babyg Brother\nTest\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n",
  "Test\nBabyg Brother\nBabycyclette\nBabytcoin\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\nBabyShark\nBabyfoot\nBabybel\nBabysounours\nBabybron\n"
  };
    EXPECT_TRUE(isValueInList(deck.dump(), possibilities));
}

TEST(Deck, empty) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    EXPECT_FALSE(deck.empty());
    for (int i = 0; i < 18; i++) {
		deck.drawCard();
	}
    EXPECT_TRUE(deck.empty());
}
