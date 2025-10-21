#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card c1;
    ASSERT_EQUAL(TWO, c1.get_rank());
    ASSERT_NOT_EQUAL(FIVE, c1.get_rank());
    ASSERT_NOT_EQUAL(EIGHT, c1.get_rank());
    ASSERT_NOT_EQUAL(KING, c1.get_rank());

}

// Add more test cases here
TEST(test_card_rank_suit) {
    Card kingDiamonds(KING, DIAMONDS);

    ASSERT_EQUAL(kingDiamonds.get_rank(), KING);
    ASSERT_EQUAL(kingDiamonds.get_suit(), DIAMONDS);
    ASSERT_NOT_EQUAL(kingDiamonds.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(kingDiamonds.get_suit(HEARTS), DIAMONDS);
}

TEST(test_card_type) {
    Card queenSpades = Card(QUEEN, SPADES);

    ASSERT_FALSE(queenSpades.is_trump(DIAMONDS));
    ASSERT_TRUE(queenSpades.is_trump(SPADES));
    ASSERT_TRUE(queenSpades.is_face_or_ace());
    ASSERT_FALSE(queenSpades.is_right_bower(DIAMONDS));
    ASSERT_FALSE(queenSpades.is_left_bower(DIAMONDS));

    Card tenHearts = Card(TEN, HEARTS);

    ASSERT_TRUE(tenHearts.is_trump(HEARTS));
    ASSERT_FALSE(tenHearts.is_face_or_ace());
    ASSERT_FALSE(tenHearts.is_right_bower(SPADES));
    ASSERT_FALSE(tenHearts.is_left_bower(SPADES));

    Card jackDiamonds = Card(JACK, DIAMONDS);

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
    ASSERT_TRUE(Card_less(jackDiamonds, kingSpades, sixSpades, HEARTS));
    ASSERT_TRUE(Card_less(jackHearts, kingDiamonds, sixSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, kingSpades, sixSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(jackHearts, kingHearts, sixHearts, HEARTS));
    ASSERT_FALSE(Card_less(jackSpades, kingSpades, sixSpades, CLUBS));
    ASSERT_FALSE(Card_less(jackClubs, kingClubs, sixClubs, CLUBS));
    ASSERT_FALSE(Card_less(jackSpades, kingSpades, sixSpades, SPADES));
    ASSERT_FALSE(Card_less(jackSpades, kingSpades, sixSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(sixHearts, sixSpades, tenHearts, CLUBS));
    ASSERT_FALSE(Card_less(jackHearts, jackHearts, jackHearts, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, jackDiamonds, jackDiamonds, DIAMONDS));
    ASSERT_TRUE(Card_less(sixSpades, sixClubs, CLUBS));
    ASSERT_TRUE(Card_less(kingSpades, sixDiamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(tenHearts, kingSpades, HEARTS));
    ASSERT_FALSE(Card_less(jackDiamonds, jackHearts, DIAMONDS));
    ASSERT_TRUE(Card_less(sixSpades, tenSpades, SPADES));
    ASSERT_FALSE(Card_less(kingClubs, jackSpades, CLUBS));
    ASSERT_TRUE(Card_less(kingSpades, jackDiamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(jackDiamonds, kingSpades, DIAMONDS));
    ASSERT_FALSE(Card_less(sixDiamonds, sixHearts, DIAMONDS));
    ASSERT_TRUE(Card_less(sixClubs, tenSpades, SPADES));
    ASSERT_TRUE(Card_less(kingSpades, jackHearts, DIAMONDS));
}

TEST(get_suit_trump) {
    //right bower
    Card jackHearts(JACK, HEARTS);
    ASSERT_EQUAL(jackHearts.get_suit(HEARTS), HEARTS);

    //left bower
    Card jackDiamonds(JACK, DIAMONDS);
    ASSERT_EQUAL(jackDiamonds.get_suit(HEARTS), HEARTS);

    //non trump Jack should not change
    Card jackClubs(JACK, CLUBS);
    ASSERT_EQUAL(jackClubs.get_suit(HEARTS), CLUBS);

    //non bower trump check
    Card queenHearts(QUEEN, HEARTS);
    ASSERT_EQUAL(queenHearts.get_suit(HEARTS), HEARTS);

    //same color but not Jack, shouldnt become trump
    Card queenDiamonds(QUEEN, DIAMONDS);
    ASSERT_EQUAL(queenDiamonds.get_suit(HEARTS), DIAMONDS);
}

TEST(test_card_get_suit_left_bower_colors) {
    //if trump = hearts, diamonds is left bower
    ASSERT_EQUAL(Card(JACK, DIAMONDS).get_suit(HEARTS), HEARTS);
    //if trump = diamonds, hearts is left bower
    ASSERT_EQUAL(Card(JACK, HEARTS).get_suit(DIAMONDS), DIAMONDS);
    //if trump = clubs, spades is left bower
    ASSERT_EQUAL(Card(JACK, SPADES).get_suit(CLUBS), CLUBS);
    //if trump = spades, clubs is left bower
    ASSERT_EQUAL(Card(JACK, CLUBS).get_suit(SPADES), SPADES);
    //opposites of every combination
    ASSERT_NOT_EQUAL(Card(JACK, CLUBS).get_suit(HEARTS), HEARTS);
    ASSERT_NOT_EQUAL(Card(JACK, DIAMONDS).get_suit(CLUBS), CLUBS);
    ASSERT_NOT_EQUAL(Card(JACK, HEARTS).get_suit(SPADES), SPADES);
    ASSERT_NOT_EQUAL(Card(JACK, SPADES).get_suit(DIAMONDS), DIAMONDS);
    ASSERT_NOT_EQUAL(Card(JACK, CLUBS).get_suit(DIAMONDS), DIAMONDS);
    ASSERT_NOT_EQUAL(Card(JACK, DIAMONDS).get_suit(SPADES), SPADES);
    ASSERT_NOT_EQUAL(Card(JACK, HEARTS).get_suit(CLUBS), CLUBS);
    ASSERT_NOT_EQUAL(Card(JACK, SPADES).get_suit(HEARTS), HEARTS);
}

TEST(test_card_is_trump_bowers) {
    //trump = Hearts
    Card jackHearts(JACK, HEARTS); //right bower
    Card jackDiamonds(JACK, DIAMONDS); //left bower
    Card queenHearts(QUEEN, HEARTS); //normal trump
    Card tenClubs(TEN, CLUBS); //non trump

    ASSERT_TRUE(jackHearts.is_trump(HEARTS)); //right bower = trump
    ASSERT_TRUE(jackDiamonds.is_trump(HEARTS)); //left bower = trump
    ASSERT_TRUE(queenHearts.is_trump(HEARTS)); //trump suit = trump
    ASSERT_FALSE(tenClubs.is_trump(HEARTS)); //different suit = not trump

    //black suits
    Card jackSpades(JACK, SPADES); //right bower, if trump = spades
    Card jackClubs(JACK, CLUBS); //left bower, if trump = spades
    ASSERT_TRUE(jackSpades.is_trump(SPADES)); //right bower
    ASSERT_TRUE(jackClubs.is_trump(SPADES)); //left bower
}

TEST(test_suit_next_pairs) {
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);

    //opposites
    ASSERT_NOT_EQUAL(Suit_next(SPADES), HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(CLUBS), DIAMONDS);
    ASSERT_NOT_EQUAL(Suit_next(HEARTS), SPADES);
    ASSERT_NOT_EQUAL(Suit_next(DIAMONDS), CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(SPADES), DIAMONDS);
    ASSERT_NOT_EQUAL(Suit_next(CLUBS), HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(HEARTS), CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(DIAMONDS), SPADES);

}

TEST(test_card_is_trump_edge_case) {
    //trump = hearts → left bower = jack of diamonds
    Card jackHearts(JACK, HEARTS);
    Card jackDiamonds(JACK, DIAMONDS);
    Card tenHearts(TEN, HEARTS);
    Card aceClubs(ACE, CLUBS);

    ASSERT_TRUE(jackHearts.is_trump(HEARTS)); //right bower
    ASSERT_TRUE(jackDiamonds.is_trump(HEARTS)); //left bower
    ASSERT_TRUE(tenHearts.is_trump(HEARTS)); //same suit
    ASSERT_FALSE(aceClubs.is_trump(HEARTS)); //non trump

    //trump = spades → left bower = jack of clubs
    Card jackSpades(JACK, SPADES);
    Card jackClubs(JACK, CLUBS);
    Card tenSpades(TEN, SPADES);
    Card aceHearts(ACE, HEARTS);

    ASSERT_TRUE(jackSpades.is_trump(SPADES)); //right bower
    ASSERT_TRUE(jackClubs.is_trump(SPADES)); //left bower
    ASSERT_TRUE(tenSpades.is_trump(SPADES)); //same suit
    ASSERT_FALSE(aceHearts.is_trump(SPADES)); //non trump
}

TEST(test_card_bowers_identification) {
    //trump = spades → next suit of same color = clubs
    Card jackSpades(JACK, SPADES);
    Card jackClubs(JACK, CLUBS);
    Card jackHearts(JACK, HEARTS);

    ASSERT_TRUE(jackSpades.is_right_bower(SPADES));
    ASSERT_FALSE(jackSpades.is_left_bower(SPADES));

    ASSERT_TRUE(jackClubs.is_left_bower(SPADES));
    ASSERT_FALSE(jackClubs.is_right_bower(SPADES));

    ASSERT_FALSE(jackHearts.is_left_bower(SPADES));
    ASSERT_FALSE(jackHearts.is_right_bower(SPADES));

    //trump = diamonds → next suit of same color = hearts
    Card jackDiamonds(JACK, DIAMONDS);

    ASSERT_TRUE(jackDiamonds.is_right_bower(DIAMONDS));
    ASSERT_FALSE(jackDiamonds.is_left_bower(DIAMONDS));

    ASSERT_TRUE(jackHearts.is_left_bower(DIAMONDS));
    ASSERT_FALSE(jackHearts.is_right_bower(DIAMONDS));

    ASSERT_FALSE(jackSpades.is_left_bower(DIAMONDS));
    ASSERT_FALSE(jackSpades.is_right_bower(DIAMONDS));
}

TEST(test_card_get_suit_of_trump_and_bowers) {
    // Hearts = trump, left bower = jack of diamonds
    Card jackHearts(JACK, HEARTS);
    Card jackDiamonds(JACK, DIAMONDS);
    Card queenHearts(QUEEN, HEARTS);
    Card nineHearts(NINE, HEARTS);
    Card aceClubs(ACE, CLUBS);

    //right bower returns own suit
    ASSERT_EQUAL(jackHearts.get_suit(HEARTS), HEARTS);

    ASSERT_ALMOST_EQUAL(jackHearts.get_suit(HEARTS), DIAMONDS, 3);

    //left bower should return trump suit
    ASSERT_EQUAL(jackDiamonds.get_suit(HEARTS), HEARTS);

    ASSERT_ALMOST_EQUAL(jackDiamonds.get_suit(DIAMONDS), HEARTS, 3);

    //other hearts are just hearts
    ASSERT_EQUAL(queenHearts.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(nineHearts.get_suit(HEARTS), HEARTS);

    //non trump-non bower returns natural suit
    ASSERT_EQUAL(aceClubs.get_suit(HEARTS), CLUBS);
}

TEST_MAIN()
