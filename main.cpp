#include <iostream>
#include "Caesar.h"

int main(int argc, char* argv[])
{
    Caesar c{8};
    const std::string msg = "Nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura";
    const std::string separator = "---\n";
    std::cout << separator
              << "Plaintext:\n"
              << "Nel mezzo del cammin di nostra vita, mi ritrovai per una selva oscura" << '\n'
              << separator
              << "Key: (shift = 8)\n"
              << c.print_shifted() << '\n'
              << separator
              << "Ciphertext:\n"
              << c.encrypt(msg) << '\n'
              << separator
              << "Decrypted:\n"
              << c.decrypt(c.encrypt(msg)) << '\n'
              << separator << std::endl;
    return 0;
}