#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_default_ctor_2) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(JACK, first.get_rank());
    ASSERT_EQUAL(HEARTS, first.get_suit());

    Card third = pack.deal_one();
    ASSERT_EQUAL(TWO, third.get_rank());
    ASSERT_EQUAL(CLUBS, third.get_suit());

    Card sixth = pack.deal_one();
    ASSERT_EQUAL(FOUR, sixth.get_rank());
    ASSERT_EQUAL(DIAMONDS, sixth.get_suit());

    Card eighteenth = pack.deal_one();
    ASSERT_EQUAL(ACE, eighteenth.get_rank());
    ASSERT_EQUAL(SPADES, eighteenth.get_suit());
    
    Card last = pack.deal_one();
    ASSERT_EQUAL(TEN, last.get_rank());
    ASSERT_EQUAL(HEARTS, last.get_suit());

    for (int i = 0; i != 7; ++i) {
        pack.deal_one();
    }

    for (int i = 0; i != 19; ++i) {
        pack.deal_one();
    }
    for (int i = 0; i != 25; ++i) {
        pack.deal_one();
    }
}

TEST_MAIN()
