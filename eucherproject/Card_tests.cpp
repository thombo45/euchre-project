#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card c1;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(FIVE, c.get_rank());
    ASSERT_EQUAL(EIGHT, c.get_rank());
    ASSERT_EQUAL(KING, c.get_rank());

    ASSERT_EQUAL(CLUBS,c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_rank());
}

// Add more test cases here
TEST(test_card_rank_suit) {
    Card kingDiamonds(KING, DIAMONDS);

    ASSERT_EQUAL(kingDiamonds.get_suit(), KING);
    ASSERT_EQUAL(kingDiamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(kingDiamonds.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(kingDiamonds.get_suit(HEARTS), DIAMONDS);
}

TEST(test_card_type) {
    Card queenSpades = Card(QUEEN, SPADES);

    ASSERT_TRUE(queenSpades.is_trump(SPADES));
    ASSERT_TRUE(queenSpades.is_face_or_ace());
    ASSERT_FALSE(queenSpades.is_right_bower(DIAMONDS));
    ASSERT_FALSE(queenSpades.is_left_bower(DIAMONDS));

    Card tenHearts = Card(TEN, HEARTS);

    ASSERT_TRUE(tenHearts.is_trump(HEARTS));
    ASSERT_FALSE(tenHearts.is_face_or_ace());
    ASSERT_FALSE(tenHearts.is_right_bower(SPADES));
    ASSERT_FALSE(tenHearts.is_left_bower(SPADES));

    Card jackDiamonds = Card(JACK, CLUBS);

    ASSERT_TRUE(jackDiamonds.is_trump(DIAMONDS));
    ASSERT_TRUE(jackDiamonds.is_face_or_ace());
    ASSERT_TRUE(jackDiamonds.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jackDiamonds.is_left_bower(HEARTS));
}

TEST(test_card_comparison) {
    Card fiveClubs = Card(FIVE, CLUBS);
    Card fourHearts = Card(FOUR, HEARTS);

    ASSERT_FALSE(fiveClubs == fourHearts);
    ASSERT_TRUE(fiveClubs > fourHearts);
    ASSERT_TRUE(fiveClubs >= fourHearts);
    ASSERT_TRUE(fiveClubs != fourHearts);
    ASSERT_FALSE(fiveClubs < fourHearts);
    ASSERT_FALSE(fiveClubs <= fourHearts);
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);

    ASSERT_NOT_EQUAL(Suit_next(HEARTS), SPADES);
    ASSERT_NOT_EQUAL(Suit_next(SPADES), HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(HEARTS), CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(CLUBS), HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(DIAMONDS), SPADES);
    ASSERT_NOT_EQUAL(Suit_next(SPADES), DIAMONDS);
    ASSERT_NOT_EQUAL(Suit_next(DIAMONDS), CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(CLUBS), DIAMONDS);
}

TEST(test_card_less) {
    Card sixHearts = Card(SIX, HEARTS);
    Card sixSpades = Card(SIX, SPADES);
    Card sixClubs = Card(SIX, CLUBS);
    Card sixDiamonds = Card(SIX, DIAMONDS);

    Card tenHearts = Card(TEN, HEARTS);
    Card tenSpades = Card(TEN, SPADES);

    Card kingHearts = Card(KING, HEARTS);
    Card kingSpades = Card(KING, SPADES);
    Card kingClubs = Card(KING, CLUBS);
    Card kingDiamonds = Card(KING, DIAMONDS);

    Card jackHearts = Card(KING, HEARTS);
    Card jackSpades = Card(KING, SPADES);
    Card jackClubs = Card(KING, CLUBS);
    Card jackDiamonds = Card(KING, DIAMONDS);

    ASSERT_FALSE(Card_less(jackHearts, kingSpades, sixSpades, HEARTS));
    ASSERT_FALSE(Card_less(jackDiamonds, kingSpades, sixSpades, HEARTS));
    ASSERT_FALSE(Card_less(jackHearts, kingDiamonds, sixSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, kingSpades, sixSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(jackHearts, kingHearts, sixHearts, HEARTS));
    ASSERT_FALSE(Card_less(jackSpades, kingSpades, sixSpades, CLUBS));
    ASSERT_FALSE(Card_less(jackClubs, kingClubs, sixClubs, CLUBS));
    ASSERT_FALSE(Card_less(jackSpades, kingSpades, sixSpades, SPADES));
    ASSERT_TRUE(Card_less(jackSpades, kingSpades, sixSpades, DIAMONDS));
    ASSERT_TRUE(Card_less(sixHearts, sixSpades, tenHearts, CLUBS));
    ASSERT_FALSE(Card_less(jackHearts, jackHearts, jackHearts, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, jackDiamonds, jackDiamonds, DIAMONDS));
    ASSERT_TRUE(Card_less(sixSpades, sixClubs, CLUBS));
    ASSERT_TRUE(Card_less(kingSpades, sixDiamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(tenHearts, kingSpades, HEARTS));
    ASSERT_FALSE(Card_less(jackDiamonds, jackHearts, DIAMONDS));
    ASSERT_TRUE(Card_less(sixSpades, tenSpades, SPADES));
    ASSERT_TRUE(Card_less(kingClubs, jackSpades, CLUBS));
    ASSERT_TRUE(Card_less(kingSpades, jackDiamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, kingSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(sixDiamonds, sixHearts, DIAMONDS));
    ASSERT_TRUE(Card_less(sixClubs, tenSpades, SPADES));
    ASSERT_TRUE(Card_less(kingSpades, jackHearts, DIAMONDS)); 
}

TEST_MAIN()
