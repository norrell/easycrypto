#include <algorithm>
#include <cctype>
#include <list>
#include <map>
#include <stdexcept>
#include <string>

class SimpleSubstitution
{
public:
    SimpleSubstitution()
    {
        generate_key();
    }

    SimpleSubstitution(const std::string& key)
    {
        try
        {
            set_key(key);
        }
        catch (std::invalid_argument& e)
        {
            throw;
        }
    }

    void set_key(std::string key)
    {
        for (int i = 0; i < key.length(); ++i)
        {
            key[i] = isupper(key[i]) ? key[i] : toupper(key[i]);
        }

        if (!is_key(key))
            throw std::invalid_argument("A key must be a permutation of the alphabet");

        key_ = key;
    }

    void generate_key()
    {
        std::string key = ALPHABET;
        std::random_shuffle(key.begin(), key.end());
        key_ = key;
    }

    std::string key() { return key_; }

    std::string decrypt(const std::string& ciphertext)
    {
        return decrypt(ciphertext, key_);
    }

    std::string decrypt(const std::string& ciphertext, const std::string key)
    {
        std::stringstream ss;

        for (auto ch : ciphertext)
        {
            ss << (isletter(ch) ? decrypt_letter(ch, key) : ch);
        }

        return ss.str();
    }

    std::string encrypt(const std::string& plaintext) const
    {
        return encrypt(plaintext, key_);
    }

    std::string encrypt(const std::string& plaintext, const std::string& key) const
    {
        std::stringstream ss;
        int i = 0;
        for (auto ch : plaintext)
        {
            if (isspace(ch) || !isletter(ch))
                continue;

            if (i == 64)
            {
                ss << '\n';
                i = 0;
            }

            if (i != 0 && i % 4 == 0)
                ss << ' ';

            ss << encrypt_letter(ch, key);
            ++i;
        }
        return ss.str();
    }

    bool isletter(char ch) const
    {
        return (65 <= ch && ch <= 90) ||  /* A..Z */
               (97 <= ch && ch <= 122);   /* a..z */
    }

    char decrypt_letter(char letter, const std::string& key) const
    {
        return ALPHABET[key.find(toupper(letter))];
    }

    char encrypt_letter(char letter, const std::string& key) const
    {
        return key[ALPHABET.find(toupper(letter))];
    }

    bool is_key(const std::string& key) const
    {
        if (key.length() != ALPHABET.length())
            return false;

        for (auto ch : ALPHABET)
        {
            std::size_t found = key.find(ch);
            if (found == std::string::npos)
                return false;
        }

        return true;
    }

    std::string alphabet() const { return ALPHABET; }

    std::map<char, int> count_occurrences(const std::string& ciphertext)
    {
        std::map<char, int> occurrences = {
            {'A', 0},
            {'B', 0},
            {'C', 0},
            {'D', 0},
            {'E', 0},
            {'F', 0},
            {'G', 0},
            {'H', 0},
            {'I', 0},
            {'J', 0},
            {'K', 0},
            {'L', 0},
            {'M', 0},
            {'N', 0},
            {'O', 0},
            {'P', 0},
            {'Q', 0},
            {'R', 0},
            {'S', 0},
            {'T', 0},
            {'U', 0},
            {'V', 0},
            {'W', 0},
            {'X', 0},
            {'Y', 0}
        };

        for (auto ch : ciphertext)
        {
            if (!isletter(ch))
                continue;

            ch = toupper(ch);
            occurrences[ch]++;
        }

        return occurrences;
    }

    std::map<int, std::list<char> > sort_by_occurrences(const std::map<char, int>& occurs)
    {
        std::map<int, std::list<char> > sorted_map;

        for (auto it : occurs)
        {
            char letter = toupper(it.first);
            int n_occurrences = it.second;
            if (sorted_map.find(n_occurrences) == sorted_map.end())
            {
                sorted_map.insert(std::pair<int, std::list<char> >(n_occurrences, {letter}));
            }
            else
            {
                (sorted_map[n_occurrences]).push_back(letter);
            }
        }

        return sorted_map;
    }

    std::string guess_key(const std::string& ciphertext)
    {
        std::map<char, int> occurrs = count_occurrences(ciphertext);
        std::map<int, std::list<char> > sorted_occurrs = sort_by_occurrences(occurrs);
        std::stringstream guessed_key;
        for (auto pair : sorted_occurrs)
        {
            for (auto elem : pair.second)
            {
                guessed_key << elem;
            }
        }
        return guessed_key.str();
    }

private:
    static const std::string ALPHABET;
    //static const std::map<char, double> LETTER_FREQS_EN;
    static const std::list<char> LETTERS_BY_FREQ_EN;
    std::string key_ = "";
};

const std::string SimpleSubstitution::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// const std::map<char, double> SimpleSubstitution::LETTER_FREQS_EN = {
//     {'A', 8.167},
//     {'B', 1.492},
//     {'C', 2.782},
//     {'D', 4.253},
//     {'E', 12.702},
//     {'F', 2.228},
//     {'G', 2.105},
//     {'H', 6.094},
//     {'I', 6.966},
//     {'J', 0.153},
//     {'K', 0.772},
//     {'L', 4.025},
//     {'M', 2.406},
//     {'N', 6.749},
//     {'O', 7.507},
//     {'P', 1.929},
//     {'Q', 0.095},
//     {'R', 5.987},
//     {'S', 6.327},
//     {'T', 9.056},
//     {'U', 2.758},
//     {'V', 0.978},
//     {'W', 2.360},
//     {'X', 0.150},
//     {'Y', 0.074}
// };

const std::list<char> SimpleSubstitution::LETTERS_BY_FREQ_EN = {
    'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W',
    'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z'
};