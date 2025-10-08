#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(add_card__get_card){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, HEARTS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, DIAMONDS);
    Card c4(JACK, SPADES);
    Card c5(NINE, HEARTS);
 
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    ASSERT_EQUAL(c1, Noah -> get_card(0));
    ASSERT_EQUAL(c2, Noah -> get_card(1));
    ASSERT_EQUAL(c3, Noah -> get_card(2));
    ASSERT_EQUAL(c4, Noah -> get_card(3));
    ASSERT_EQUAL(c5, Noah -> get_card(4));
    
    delete Noah;
}

TEST(will_make_trump_round_1){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, HEARTS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, DIAMONDS);
    Card c4(JACK, SPADES);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, true, 1, Order_up);
    
    ASSERT_EQUAL(Order_up, UpC.get_suit());
    
    delete Noah;
}
TEST(will_definitly_make_trump_round_1){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, CLUBS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, CLUBS);
    Card c4(KING, CLUBS);
    Card c5(NINE, CLUBS);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, true, 1, Order_up);
    
    ASSERT_EQUAL(Order_up, UpC.get_suit());
    
    delete Noah;
}
TEST(will_definitly_2_make_trump_round_1){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, CLUBS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, CLUBS);
    Card c4(KING, CLUBS);
    Card c5(JACK, SPADES);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, true, 1, Order_up);
    
    ASSERT_EQUAL(Order_up, UpC.get_suit());
    
    delete Noah;
}

TEST(will_not_make_trump_round_1){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, HEARTS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    
    ASSERT_EQUAL(false, Noah -> make_trump(UpC, true, 1, Order_up));
    
    delete Noah;
}

TEST(will_make_trump_round_2_not_dealer_LB){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, HEARTS);
    Card c2(JACK, SPADES);
    Card c3(ACE, HEARTS);
    Card c4(KING, HEARTS);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, false, 2, Order_up);
    
    ASSERT_EQUAL(Order_up, SPADES);
    
    delete Noah;
}

TEST(will_make_trump_round_2_not_dealer_RB){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, HEARTS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, HEARTS);
    Card c4(KING, HEARTS);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, false, 2, Order_up);
    
    ASSERT_EQUAL(Order_up, SPADES);
    
    delete Noah;
}

TEST(will_not_make_trump_round_2_not_dealer){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, SPADES);
    Card c2(KING, CLUBS);
    Card c3(ACE, HEARTS);
    Card c4(JACK, HEARTS);
    Card c5(NINE, SPADES);
    
    Card UpC(TWO, CLUBS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    
    ASSERT_EQUAL(false, Noah -> make_trump(UpC, false, 2, Order_up));
    
    delete Noah;
}


TEST(will_make_trump_round_2_is_dealer){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(TWO, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, CLUBS);
    Card c4(KING, CLUBS);
    Card c5(NINE, CLUBS);
    
    Card UpC(TWO, HEARTS);
    Suit Order_up;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> make_trump(UpC, true, 2, Order_up);
    
    ASSERT_EQUAL(Order_up, DIAMONDS);
    
    delete Noah;
}

TEST(add_discard_UpCard){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, CLUBS);
    Card c4(KING, CLUBS);
    Card c5(NINE, CLUBS);
    
    Card UpC(TWO, HEARTS);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> add_and_discard(UpC);
    
    ASSERT_NOT_EQUAL(Noah -> get_card(0), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(1), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(2), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(3), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(4), UpC);
}

TEST(add_discard_Keep_UpCard){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(ACE, CLUBS);
    Card c4(KING, CLUBS);
    Card c5(NINE, CLUBS);
    
    Card UpC(TWO, HEARTS);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> add_and_discard(UpC);
    
    ASSERT_NOT_EQUAL(Noah -> get_card(0), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(1), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(2), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(3), UpC);
    ASSERT_NOT_EQUAL(Noah -> get_card(4), UpC);
}

// Add more tests here

TEST_MAIN()
