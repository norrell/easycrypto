#include <gmock/gmock.h>
#include "Caesar.h"

using namespace testing;

class CaesarCipher
: public Test
{
public:
    Caesar caesar;
};


TEST_F(CaesarCipher, ShiftsLetterByPositiveNumber)
{
    ASSERT_THAT(caesar.shift('A', 5), Eq('F'));
}

TEST_F(CaesarCipher, ShiftsLetterByNegativeNumber)
{
    ASSERT_THAT(caesar.shift('F', -5), Eq('A'));
}

TEST_F(CaesarCipher, ConvertsToUppercaseWhenShifting)
{
    ASSERT_THAT(caesar.shift('i', 3), Eq('L'));
}

TEST_F(CaesarCipher, WrapsAroundWhenReachedEndOfAlphabet)
{
    ASSERT_THAT(caesar.shift('b', -6), Eq('V'));
}

TEST_F(CaesarCipher, ThrowsExceptionForNonAlphabeticCharacters)
{
    ASSERT_THROW(caesar.shift('7', 4), CipherException);
}

TEST_F(CaesarCipher, ShiftsAllLettersInString)
{
    ASSERT_THAT(caesar.encrypt("abcd", 4), Eq("EFGH"));
}

TEST_F(CaesarCipher, RemovesWhiteSpaceCharacters)
{
    ASSERT_THAT(caesar.encrypt("ab cd", 4), Eq("EFGH"));
}

TEST_F(CaesarCipher, EncryptsPlaintextInBlocksOfFour)
{
    ASSERT_THAT(caesar.encrypt("Nel mezzo del cammin", 1), Eq("OFMN FAAP EFMD BNNJ O"));
}

TEST_F(CaesarCipher, DecryptsUsingSameShiftAmountAsEncryption)
{
    ASSERT_THAT(caesar.decrypt("EFGH", 4), Eq("ABCD"));
}

TEST_F(CaesarCipher, EncryptsWithMemberShiftAmount)
{
    Caesar caesar1{1};

    ASSERT_THAT(caesar1.encrypt("Nel mezzo del cammin"), Eq("OFMN FAAP EFMD BNNJ O"));
}

TEST_F(CaesarCipher, IgnoresPunctuationMarks)
{
    ASSERT_THAT(caesar.encrypt("Io, tu"), Eq("IOTU"));
}

TEST_F(CaesarCipher, PrintsTheKey)
{
    ASSERT_THAT(caesar.print_shifted(), Eq("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}