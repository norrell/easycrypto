#include <gmock/gmock.h>
#include <map>
#include <sstream>
#include "SimpleSubstitution.h"

using namespace testing;

class SimpleSubstitutionCipher
: public Test
{
public:
    SimpleSubstitution s;
};

TEST_F(SimpleSubstitutionCipher, SwapsPlaintextLetterWithMatchingLetterFromTheKey)
{
    ASSERT_EQ('Q', s.encrypt_letter('A', "QWERTZUIOPLKJHGFDSAYXCVBNM"));
}

TEST_F(SimpleSubstitutionCipher, ConvertsLowercaseLetterToUppercase)
{
    ASSERT_EQ('Q', s.encrypt_letter('a', "QWERTZUIOPLKJHGFDSAYXCVBNM"));
}

TEST_F(SimpleSubstitutionCipher, EncryptsPlaintextWithGivenKey)
{
    ASSERT_EQ("QWER", s.encrypt("abcd", "QWERTZUIOPLKJHGFDSAYXCVBNM"));
}

TEST_F(SimpleSubstitutionCipher, ChecksIfGivenKeyIsValid)
{
    ASSERT_TRUE(s.is_key("QWERTZUIOPLKJHGFDSAYXCVBNM"));
    ASSERT_FALSE(s.is_key("EEEEEEEEEEEEEEEEEEEEEERZTC"));
}

TEST_F(SimpleSubstitutionCipher, TakesOptionalKeyAtConstruction)
{
    SimpleSubstitution s1{"QWERTZUIOPLKJHGFDSAYXCVBNM"};
    ASSERT_EQ("QWERTZUIOPLKJHGFDSAYXCVBNM", s1.key());
}

TEST_F(SimpleSubstitutionCipher, ConvertsConstructorKeyToUppercase)
{
    s.set_key("qwertzuioplkjhgfdsayxcvbnm");
    ASSERT_EQ("QWERTZUIOPLKJHGFDSAYXCVBNM", s.key());
}

TEST_F(SimpleSubstitutionCipher, GeneratesARandomKey)
{
    s.generate_key();
    ASSERT_TRUE(s.is_key(s.key()));
}

TEST_F(SimpleSubstitutionCipher, GeneratesRandomKeyAtConstruction)
{
    ASSERT_TRUE(s.is_key(s.key()));
}

TEST_F(SimpleSubstitutionCipher, IgnoresWhitespaceDuringEncryption)
{
    s.set_key("qwertzuioplkjhgfdsayxcvbnm");
    ASSERT_EQ("HTKJ", s.encrypt("Nel m"));
}

TEST_F(SimpleSubstitutionCipher, IgnoresNonAlphabeticCharactersDuringEncryption)
{
    s.set_key("qwertzuioplkjhgfdsayxcvbnm");
    ASSERT_EQ("HTKJ", s.encrypt("Nel56##m"));
}

TEST_F(SimpleSubstitutionCipher, EncryptsPlaintextInBlocksOfFour)
{
    s.set_key("qwertzuioplkjhgfdsayxcvbnm");
    ASSERT_EQ("HTKJ TMMG", s.encrypt("Nel mezzo"));
}

TEST_F(SimpleSubstitutionCipher, SwapsCiphertextLetterWithMatchingLetterFromTheAlphabet)
{
    ASSERT_EQ('N', s.decrypt_letter('H', "QWERTZUIOPLKJHGFDSAYXCVBNM"));
}

TEST_F(SimpleSubstitutionCipher, DecryptsCiphertextWithGivenKey)
{
    ASSERT_EQ("NELM", s.decrypt("HTKJ", "QWERTZUIOPLKJHGFDSAYXCVBNM"));
}

TEST_F(SimpleSubstitutionCipher, KeepsNonAlphabeticCharactersDuringDecryption)
{
    s.set_key("qwertzuioplkjhgfdsayxcvbnm");
    ASSERT_EQ("NEL6 7#M", s.decrypt("HTK6 7#J"));
}

// TEST_F(SimpleSubstitutionCipher, CountsOccurrencesOfLetterInCiphertext)
// {
//     int occ = s.occurrences_of('A', "ACFV DFEA ADDD");
//     ASSERT_EQ(3, occ);
// }

TEST_F(SimpleSubstitutionCipher, BuildsMapOfLetterOccurrencesInCiphertext)
{
    std::map<char, int> occurrences = s.count_occurrences("ACFV DFEA ADDD");
    ASSERT_EQ(3, occurrences['A']);
    ASSERT_EQ(4, occurrences['D']);
    ASSERT_EQ(0, occurrences['Z']);
}

TEST_F(SimpleSubstitutionCipher, BuildsMapSortedByLetterOccurrences)
{
    std::map<char, int> occurrences = s.count_occurrences("ABBC CCCC ERZT");
    std::map<int, std::list<char> > sorted = s.sort_by_occurrences(occurrences);
    ASSERT_EQ('C', (sorted[5]).front());
    std::stringstream ss;
    for (auto elem : sorted[1])
        ss << elem;
    ASSERT_EQ("AERTZ", ss.str());
}

TEST_F(SimpleSubstitutionCipher, CalculatesFirstGuessOfUnknownKey)
{
    const std::string plaintext = "In a simple substitution cipher, each letter of the plaintext is replaced with another, and any particular letter in the plaintext will always be transformed into the same letter in the ciphertext. For instance, if all occurrences of the letter e turn into the letter X, a ciphertext message containing numerous instances of the letter X would suggest to a cryptanalyst that X represents e.\nThe basic use of frequency analysis is to first count the frequency of ciphertext letters and then associate guessed plaintext letters with them. More Xs in the ciphertext than anything else suggests that X corresponds to e in the plaintext, but this is not certain; t and a are also very common in English, so X might be either of them also. It is unlikely to be a plaintext z or q which are less common. Thus the cryptanalyst may need to try several combinations of mappings between ciphertext and plaintext letters.\nMore complex use of statistics can be conceived, such as considering counts of pairs of letters (bigrams), triplets (trigrams), and so on. This is done to provide more information to the cryptanalyst, for instance, Q and U nearly always occur together in that order in English, even though Q itself is rare.";
    const std::string ciphertext = s.encrypt(plaintext);
    std::string guessed_key = s.guess_key(ciphertext);
    ASSERT_TRUE(s.is_key(guessed_key)) << guessed_key;
}