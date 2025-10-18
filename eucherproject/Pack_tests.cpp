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
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());

    Card third = pack.deal_one();
    ASSERT_EQUAL(TEN, third.get_rank());
    ASSERT_NOT_EQUAL(HEARTS, third.get_suit());


    for (int i = 0; i != 19; ++i) {
        pack.deal_one();
    }

    Card eighteenth = pack.deal_one();
    ASSERT_EQUAL(QUEEN, eighteenth.get_rank());
    ASSERT_EQUAL(DIAMONDS, eighteenth.get_suit());

    for (int i = 0; i != 25; ++i) {
        pack.deal_one();
    }
    
    Card last = pack.deal_one();
    ASSERT_EQUAL(THREE, last.get_rank());
    ASSERT_EQUAL(SPADES, last.get_suit());
}

TEST_MAIN()
