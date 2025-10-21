#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(PLAY_CARD_when_left_bower_is_led){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(NINE, CLUBS);
    Card c2(TEN, CLUBS);
    Card c3(QUEEN, DIAMONDS);
    
    Card led(JACK, CLUBS);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Card test = Noah -> play_card(led, SPADES);
    ASSERT_EQUAL(test, c1);
    delete Noah;
    
}

TEST(add_card__play_card){
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
    Card c1(THREE, HEARTS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, HEARTS);
    Card c4(KING, HEARTS);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, HEARTS);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> add_and_discard(UpC);

    delete Noah;
}
TEST(add_discard_UpCard_only_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, HEARTS);
    Card c2(JACK, DIAMONDS);
    Card c3(ACE, HEARTS);
    Card c4(KING, CLUBS);
    Card c5(NINE, HEARTS);
    
    Card UpC(TWO, SPADES);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> add_and_discard(UpC);

    delete Noah;
}

TEST(add_discard_Keep_UpCard){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, HEARTS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, HEARTS);
    Card c4(KING, HEARTS);
    Card c5(KING, CLUBS);
    
    Card UpC(TEN, HEARTS);
    Card Test(KING, CLUBS);
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    Noah -> add_and_discard(UpC);

    delete Noah;
    }

TEST(lead_card_all_non_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, HEARTS);
    Card c2(JACK, SPADES);
    Card c3(ACE, HEARTS);
    Card c4(KING, HEARTS);
    Card c5(KING, CLUBS);
    
    Suit s = DIAMONDS;
    Card test;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    test = Noah -> lead_card(s);
    
    ASSERT_TRUE(test == c3);

    delete Noah;
    
}

TEST(lead_card_with_trump_and_LB){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(THREE, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, HEARTS);
    Card c5(QUEEN, CLUBS);
    
    Suit s = DIAMONDS;
    Card test;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    test = Noah -> lead_card(s);
    
    
    ASSERT_TRUE(test == c4);

    delete Noah;
    
}

TEST(lead_card_all_trump_RB_vs_LB){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit s = DIAMONDS;
    Card test;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    test = Noah -> lead_card(s);
    
    
    ASSERT_TRUE(test == c1);

    delete Noah;
}
TEST(play_card_follow_suit_not_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit trump = CLUBS;
    Card card_led(TWO, DIAMONDS);
    Card card_played;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    card_played = Noah -> play_card(card_led, trump);
    
    ASSERT_TRUE(card_played == c3);

    delete Noah;
}

TEST(play_card_follow_suit_with_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit trump = DIAMONDS;
    Card card_led(TWO, DIAMONDS);
    Card card_played;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    card_played = Noah -> play_card(card_led, trump);
    
    cout << card_played << " == " << c1<< endl;
    
    delete Noah;
}

TEST(play_card_cant_follow_suit_no_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(THREE, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit trump = CLUBS;
    Card card_led(TWO, CLUBS);
    Card card_played;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    card_played = Noah -> play_card(card_led, trump);
    
    ASSERT_TRUE(card_played == c2);
    
    delete Noah;
    
}
TEST(play_card_cant_follow_suit_with_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(THREE, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit trump = HEARTS;
    Card card_led(TWO, CLUBS);
    Card card_played;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    card_played = Noah -> play_card(card_led, trump);
    
    cout << card_played << " == " << c5 << endl;

    ASSERT_TRUE(card_played == c5);
    
    delete Noah;
    
}

TEST(play_card_cant_follow_suit_all_trump){
    Player * Noah = Player_factory("Noah", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(KING, DIAMONDS);
    Card c5(QUEEN, DIAMONDS);
    
    Suit trump = DIAMONDS;
    Card card_led(TWO, CLUBS);
    Card card_played;
    
    Noah -> add_card(c1);
    Noah -> add_card(c2);
    Noah -> add_card(c3);
    Noah -> add_card(c4);
    Noah -> add_card(c5);
    
    card_played = Noah -> play_card(card_led, trump);
    
    cout << card_played << " == " << c5 << endl;

    ASSERT_TRUE(card_played == c5);

    delete Noah;
    
}

// Add more tests here

TEST_MAIN()
