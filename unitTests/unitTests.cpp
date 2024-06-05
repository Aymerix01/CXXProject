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

const std::string s = R"(<?xml version = "1.0"?>
						   <root>
							<ExplodingCard name="Baby Boom"/>
							<ExplodingCard name="Dynamite"/>
							<ExplodingCard name="TNT"/>
						   </root>)";
template <typename T>
bool isValueInList(const T& value, const std::vector<T>& list) {
    return std::ranges::find(list.begin(), list.end(), value) != list.end();
}

TEST(Deck, Constructeur) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
	Deck deck(root, sprite, eventCardManager);

    std::string expected = "Baby Boom\nDynamite\nTNT\n";
	EXPECT_EQ(deck.dump(), expected);
}

TEST(Deck, showSomeCards) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	pugi::xml_node root = doc.child("root");
	Deck deck(root, sprite, eventCardManager);

	auto cards = deck.showSomeCards(3);
	std::string expected = "TNT\nDynamite\nBaby Boom\n";
	std::string resultStr = "";
    for (auto c : cards) {
		resultStr += c->getName() + "\n";
	}
	EXPECT_EQ(resultStr, expected);
}

TEST(Deck, shuffle) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    deck.shuffle();
    std::vector<std::string> possibilities = { "Baby Boom\nDynamite\nTNT\n", 
                                                "Baby Boom\nTNT\nDynamite\n", 
                                                "Dynamite\nBaby Boom\nTNT\n", 
                                                "Dynamite\nTNT\nBaby Boom\n", 
                                                "TNT\nBaby Boom\nDynamite\n", 
                                                "TNT\nDynamite\nBaby Boom\n" };
    
    EXPECT_TRUE(isValueInList(deck.dump(), possibilities));
}

TEST(Deck, draw) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    //On v�rifie que la carte tir�e est bien la premi�re de la liste
    auto drawC = deck.drawCard()->getName();
    std::string expected = "TNT";
    EXPECT_EQ(drawC, expected);

    //On v�rifie que la carte tir�e pr�c�demment n'est plus dans le deck
    expected = "Baby Boom\nDynamite\n";
    EXPECT_EQ(deck.dump(), expected);
}

TEST(Deck, addCardToRandom) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

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

    std::vector<std::string> possibilities = { "Baby Boom\nDynamite\nTNT\nTest\n",
                                                "Baby Boom\nDynamite\nTest\nTNT\n",
                                                "Baby Boom\nTest\nDynamite\nTNT\n",
                                                "Test\nBaby Boom\nDynamite\nTNT\n" };
    EXPECT_TRUE(isValueInList(deck.dump(), possibilities));
}

TEST(Deck, empty) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	pugi::xml_node root = doc.child("root");
	Deck deck(root, sprite, eventCardManager);

	EXPECT_FALSE(deck.empty());
	deck.drawCard();
	deck.drawCard();
	deck.drawCard();
	EXPECT_TRUE(deck.empty());
}

TEST(Player, drawCard) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    //v�rifie que drawCard() ajoute bien une carte � la main du joueur
    Player player("Jean Jacques");
    player.drawCard(deck);
    player.drawCard(deck);
    player.drawCard(deck);
    std::string expected = "TNT\nDynamite\nBaby Boom\n";

    auto cardsInHand = player.dump();

    ASSERT_EQ(cardsInHand,expected);
}


TEST(Player, hasLost) {
    EventCardManager eventCardManager;
    const std::string str = R"(<?xml version = "1.0"?>
						   <root>
							<DefuseCard name="Defuse"/>
							<ExplodingCard name="Bomb"/>
							<HappyCard name="Happy"/>
						   </root>)";
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(str.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    Player player("Jean Jacques");
    player.drawCard(deck);
    EXPECT_TRUE(!player.hasLost());  
    player.drawCard(deck);
    EXPECT_TRUE(player.hasLost());
    player.drawCard(deck);
    EXPECT_TRUE(!player.hasLost());
}

TEST(Card, playCard) {
    EventCardManager eventCardManager;
    const std::string str = R"(<?xml version = "1.0"?>
						   <root>
                            <ShuffleCard name="Shuffle"/>
							<ExplodingCard name="Exploding"/>
                            <AttackCard name="Attack"/>
							<FutureCard name="Future"/>
							<HappyCard name="Happy"/>
						   </root>)";
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(str.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    Player player("Jean Jacques");

    player.drawCard(deck);
    player.playCard(0);
    EXPECT_TRUE(player.getScore() == 100);

    player.drawCard(deck);
    auto vector = deck.showSomeCards(3);
    EXPECT_TRUE(vector[0]->getClassType() == "AttackCard");
    EXPECT_TRUE(vector[1]->getClassType() == "ExplodingCard");
    EXPECT_TRUE(vector[2]->getClassType() == "ShuffleCard");
    
    //player.drawCard(deck);
    //player.playCard(2, deck);
    //EXPECT_TRUE(player.getScore() == 1100);
    
}