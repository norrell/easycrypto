#include <algorithm>
#include <cctype>
#include <exception>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>

class CipherException
: std::runtime_error
{
public:
    explicit CipherException(const std::string& error)
        : runtime_error(error)
    {
    }
};

class Caesar
{
public:
    Caesar()
        : shift_amount_{0}
    {
    }

    Caesar(int shift_amount)
        : shift_amount_{shift_amount}
    {
    }

    std::string decrypt(const std::string& str) const;
    std::string decrypt(const std::string& ciphertext, int shift_amout) const;
    std::string encrypt(const std::string& str) const;
    std::string encrypt(const std::string& str, int shift_amount) const;
    char shift(char letter, int shift_amount) const;
    std::string print_key(int shift_amount) const;
    std::string print_key() const;
    int shift_amount() const { return shift_amount_; }
    std::string alphabet() const { return ALPHABET; }

private:
    bool isletter(char ch) const;
    bool ispunctuation(char ch) const;
    unsigned int wrap_around(std::size_t index, int amount) const
    {
        return ((ALPHABET.length() + index + amount) % ALPHABET.length());
    }

    int shift_amount_;
    static const std::string ALPHABET;
};
