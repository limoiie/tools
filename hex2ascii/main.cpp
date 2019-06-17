#include <iostream>

#include "clipp.h"

using namespace clipp;
using std::string;
using std::cout;

string to_char(string const& hex);

int main(int argc, char **argv) {
    bool prefix0x = false;
    string str;
    auto cli = (value("input string", str),
            option("-0", "--prefix0").set(prefix0x).doc("string with 0x prefix"));
    if (!parse(argc, argv, cli))
        cout << make_man_page(cli, argv[0]);

    std::cout << to_char(str) << std::endl;
    return 0;
}

uint hex_char2num(char x) {
    auto const n = x-'0';
    if (n >= 0 && n < 10) return static_cast<uint>(n);
    return static_cast<uint>(x-'a'+10);
}

char byte2char(const char byte[2]) {
    return hex_char2num(byte[0]) + (hex_char2num(byte[1]) << (unsigned) 4);
}

string to_char(string const& hex) {
    string chars;
    char byte[2];
    for (auto i = 0; i < hex.size(); i+=2) {
        byte[1] = tolower(hex[i]);
        byte[0] = tolower(hex[i+1]);
        chars.push_back(byte2char(byte));
    }
    return chars;
}