#include "Caesar.h"

const std::string Caesar::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


std::string Caesar::decrypt(const std::string& str) const
{
    std::string plaintext;
    try
    {
        plaintext = decrypt(str, shift_amount_);
    }
    catch (CipherException& e)
    {
        throw;
    }
    return plaintext;
}

std::string Caesar::decrypt(const std::string& ciphertext, int shift_amout) const
{
    std::string plaintext;
    try
    {
        plaintext = encrypt(ciphertext, -1 * shift_amout);
    }
    catch (CipherException& e)
    {
        throw;
    }
    return plaintext;
}

std::string Caesar::encrypt(const std::string& str) const
{
    std::string ciphertext;
    try
    {
        ciphertext = encrypt(str, shift_amount_);
    }
    catch (CipherException& e)
    {
        throw;
    }
    return ciphertext;
}

std::string Caesar::encrypt(const std::string& str, int shift_amount) const
{
    std::stringstream ciphertext;

    int i = 0;
    for (auto ch : str)  // try replacing with std::for_each
    {
        if (!isletter(ch) || isspace(ch))
            continue;

        if (i > 0 && i % 4 == 0)
            ciphertext << " ";

        try {
            ciphertext << shift(ch, shift_amount);
        }
        catch (CipherException& e)
        {
            throw;
        }
        ++i;
    }

    return ciphertext.str();
}

char Caesar::shift(char ch, int shift_amount) const
{
    if (!isletter(ch))
        throw CipherException("Only letters of the alphabet can be encrypted/decrypted");

    return ALPHABET[wrap_around(ALPHABET.find(toupper(ch)), shift_amount)];
}

std::string Caesar::print_key() const
{
    std::string shifted;
    try
    {
        shifted = print_key(shift_amount_);
    }
    catch (CipherException& e)
    {
        throw;
    }
    return shifted;
}


std::string Caesar::print_key(int shift_amount) const
{
    std::string shifted(ALPHABET.length(), ' ');
    for (int i = 0; i < ALPHABET.length(); ++i)
    {
        try
        {
            shifted[i] = shift(ALPHABET[i], shift_amount);
        }
        catch (CipherException& e)
        {
            throw;
        }
    }
    return shifted;
}


bool Caesar::isletter(char ch) const
{
    return (65 <= ch && ch <= 90) ||  /* A..Z */
           (97 <= ch && ch <= 122);   /* a..z */
}

bool Caesar::ispunctuation(char ch) const
{
    switch (ch)
    {
    case '!':
    case '\"':
    case '?':
    case ',':
    case '.':
    case '\'':
    case ';':
    case ':':
    case '-':
    case '(':
    case ')':
    case 96:
        return true;
    default:
        return false;
    }
}
