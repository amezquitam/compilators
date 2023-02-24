#include <gtest/gtest.h>
#include <alphabet.hpp>

TEST(AlphabetTest, IsOnAlgorithm) 
{
    Alphabet V = { "Vowels", "aeiou" };
    Alphabet C = { "Consonants", "bcdfghjklmnpqrstvwxyz" };
    Alphabet L = { "Letters", V + C };
    Alphabet L2 = { "Letters", L };

    ASSERT_TRUE(V.has('a'));
    ASSERT_TRUE(L.has('m'));
    ASSERT_TRUE(L.has('z'));
    ASSERT_TRUE(L.has('b'));
    ASSERT_FALSE(C.has('a'));
}