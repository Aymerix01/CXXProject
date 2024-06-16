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


TEST(Player, drawCard) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    //vérifie que drawCard() ajoute bien une carte à la main du joueur
    Player player("Jean Jacques");
    player.drawCard(deck);
    player.drawCard(deck);
    player.drawCard(deck);
    std::string expected = "Babybron\nBabysounours\nBabybel\n";

    auto cardsInHand = player.dump();

    ASSERT_EQ(cardsInHand, expected);
}


TEST(Player, hasLost) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    Player player("Jean Jacques");
    player.drawCard(deck);
    EXPECT_TRUE(!player.hasLost(deck));
    player.getExplodingCard(deck);
    EXPECT_TRUE(player.hasLost(deck));
    player.getDefuseCard(deck);
    EXPECT_TRUE(!player.hasLost(deck));
}


TEST(Card, playCard) {
    EventCardManager eventCardManager;
    Deck deck(eventCardManager);

    Player player("Jean Jacques");

    eventCardManager.addEventCardListener(&player);
    eventCardManager.addEventCardListener(&deck);

    player.drawCard(deck);
    player.playCard(0);
    EXPECT_TRUE(player.getScore() == 100);
}