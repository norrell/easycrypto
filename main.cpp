#include <iostream>
#include <sstream>
#include <string>

#include "Caesar.h"
#include "SimpleSubstitution.h"

void do_caesar()
{
    Caesar c{8};
    const std::string msg = "Nel mezzo del cammin di nostra vita, mi ritrovai per una selva oscura";
    const std::string separator = "---\n";

    std::cout << "*** CAESAR CIPHER ***" << std::endl;
    std::cout << separator
              << "Plaintext:\n"
              << msg << '\n'
              << separator
              << "Key: (shift = " << c.shift_amount() << ")\n"
              << c.print_key() << '\n'
              << separator
              << "Ciphertext:\n"
              << c.encrypt(msg) << '\n'
              << separator
              << "Correspondence:\n"
              << c.print_key() << '\n'
              << c.alphabet() << '\n'
              << separator
              << "Plaintext after decryption:\n"
              << c.decrypt(c.encrypt(msg)) << '\n'
              << separator << std::endl;
}

void do_simple_substitution()
{
    SimpleSubstitution s;
    s.generate_key();
    const std::string msg = "Nel mezzo del cammin di nostra vita, mi ritrovai per una selva oscura\n"
                            "che la diritta via era smarrita!";
    const std::string separator = "---\n";

    std::cout << "*** SUBSTITUTION CIPHER ***" << std::endl;
    std::cout << separator
              << "Plaintext:\n"
              << msg << '\n'
              << separator
              << "Random key: " << s.key() << '\n'
              << separator
              << "Ciphertext:\n"
              << s.encrypt(msg) << '\n'
              << separator
              << "Correspondence:\n"
              << s.key() << '\n'
              << s.alphabet() << '\n'
              << separator
              << "Plaintext after decryption:\n"
              << s.decrypt(s.encrypt(msg)) << '\n'
              << separator << std::endl;

}

void do_frequency_analysis()
{
    SimpleSubstitution s;
    std::string key = s.key();
    std::cout << "Key = " << key << std::endl;
    std::cout << "---" << std::endl;

    const std::string plaintext = "In a simple substitution cipher, each letter of the plaintext is replaced with another, and any particular letter in the plaintext will always be transformed into the same letter in the ciphertext. For instance, if all occurrences of the letter e turn into the letter X, a ciphertext message containing numerous instances of the letter X would suggest to a cryptanalyst that X represents e.\nThe basic use of frequency analysis is to first count the frequency of ciphertext letters and then associate guessed plaintext letters with them. More Xs in the ciphertext than anything else suggests that X corresponds to e in the plaintext, but this is not certain; t and a are also very common in English, so X might be either of them also. It is unlikely to be a plaintext z or q which are less common. Thus the cryptanalyst may need to try several combinations of mappings between ciphertext and plaintext letters.\nMore complex use of statistics can be conceived, such as considering counts of pairs of letters (bigrams), triplets (trigrams), and so on. This is done to provide more information to the cryptanalyst, for instance, Q and U nearly always occur together in that order in English, even though Q itself is rare.";
    std::cout << "Plaintext:\n" << "---\n" << plaintext << "---" << std::endl;

    const std::string ciphertext = s.encrypt(plaintext);
    std::cout << "Ciphertext:\n" << "---\n" << ciphertext << "\n---" << std::endl;

    std::map<char, int> occurrences = s.count_occurrences(ciphertext);
    std::cout << "Occurrences:\n" << "---" << std::endl;
    for (auto p : occurrences)
    {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    std::map<int, std::list<char> > sorted_occs = s.sort_by_occurrences(occurrences);
    std::cout << "Sorted occurrences:\n" << "---" << std::endl;
    for (auto p : sorted_occs)
    {
        std::cout << p.first << ": ";
        for (auto listelem : p.second)
            std::cout << listelem << ", ";
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
//     do_caesar();
//     do_simple_substitution();
    do_frequency_analysis();

    return 0;
}