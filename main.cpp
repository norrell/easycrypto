#include <iostream>
#include <sstream>
#include <string>
#include "Caesar.h"

void do_caesar()
{
    Caesar c{8};
    const std::string msg = "Nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura";
    const std::string separator = "---\n";
    std::cout << separator
              << "Plaintext:\n"
              << "Nel mezzo del cammin di nostra vita, mi ritrovai per una selva oscura" << '\n'
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
              << c.decrypt(c.encrypt(msg)) << '\n'
              << separator << std::endl;
}

int main(int argc, char* argv[])
{
    do_caesar();

    return 0;
}