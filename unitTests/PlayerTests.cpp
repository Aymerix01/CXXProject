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

TEST(Player, drawCard) {
    EventCardManager eventCardManager;
    sf::Sprite sprite;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node root = doc.child("root");
    Deck deck(root, sprite, eventCardManager);

    //vérifie que drawCard() ajoute bien une carte à la main du joueur
    Player player("Jean Jacques");
    player.drawCard(deck);
    player.drawCard(deck);
    player.drawCard(deck);
    std::string expected = "TNT\nDynamite\nBaby Boom\n";

    auto cardsInHand = player.dump();

    ASSERT_EQ(cardsInHand, expected);
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

    eventCardManager.addEventCardListener(&player);
    eventCardManager.addEventCardListener(&deck);

    player.drawCard(deck);
    player.playCard(0);
    EXPECT_TRUE(player.getScore() == 100);

    player.drawCard(deck);
    auto vector = deck.showSomeCards(3);
    EXPECT_TRUE(vector[0]->getClassType() == "AttackCard");
    EXPECT_TRUE(vector[1]->getClassType() == "ExplodingCard");
    EXPECT_TRUE(vector[2]->getClassType() == "ShuffleCard");

    player.drawCard(deck);
    player.playCard(1);
    EXPECT_TRUE(player.getScore() == 1100);
}