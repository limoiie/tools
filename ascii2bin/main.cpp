#include <iostream>

#include "clipp.h"

using namespace clipp;
using std::string;
using std::cout;

using namespace std;

string to_hex(string const &str, bool with_0x, bool up_case);

int main(int argc, char **argv) {
    bool with_0x_prefix = false;
    bool up_case = false;
    string str;
    auto cli = (value("input string", str),
            option("-0", "--0x").set(with_0x_prefix).doc("output byte with 0x prefix"),
            option("-u", "--upper").set(up_case).doc("output hex in upper case")
    );
    if (!parse(argc, argv, cli))
        cout << make_man_page(cli, argv[0]);

    std::cout << to_hex(str, with_0x_prefix, up_case) << std::endl;
    return 0;
}

constexpr char look_up_table[] = "0123456789abcdef";

string to_hex(string const &str, bool with_0x, bool up_case) {
    string hex;
    char byte_0x[] = "0x??";
    char * byte = byte_0x + 2;

    for (u_char c : str) {
        unsigned low_byte = static_cast<unsigned>(0x0f) & c;
        c >>= static_cast<unsigned>(4);
        unsigned high_byte = static_cast<unsigned>(0x0f) & c;

        byte[0] = look_up_table[high_byte];
        byte[1] = look_up_table[low_byte];
        if (up_case) {
            byte[0] = std::toupper(byte[0]);
            byte[1] = std::toupper(byte[1]);
        }

        hex.append(with_0x ? byte_0x : byte).push_back(' ');
    }
    if (!hex.empty())
        hex.pop_back();
    return hex;
}