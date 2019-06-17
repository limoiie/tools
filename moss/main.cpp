#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "clipp.h"

using namespace clipp;
using std::string;
using std::cout;

using namespace std;

string decode(string &str, char break_by, char short_char, char long_char);

string encode(string const& str);

int main(int argc, char **argv) {
    char break_by = ' ';
    char short_byte = '.';
    char long_byte = '-';
    bool to_decode = false;
    string str;
    auto cli = (value("input string", str),
            option("-d", "--decode").set(to_decode).doc("decode string"),
            (option("-b", "--break") & value("break", break_by)).doc("break by"),
            (option("-s", "--short") & value("char", short_byte)).doc("short char"),
            (option("-l", "--long") & value("char", long_byte)).doc("long char")
            );
    if (!parse(argc, argv, cli))
        cout << make_man_page(cli, argv[0]);

    if (to_decode)
        std::cout << decode(str, break_by, short_byte, long_byte) << endl;
    else
        std::cout << encode(str) << endl;
    return 0;
}

std::map<string, string> const& make_encode_table() {
    static std::map<string, string> encode_table = {
            {"A", ".-"},
            {"B", "-..."},
            {"C", "-.-."},
            {"D", "-.."},
            {"E", "."},
            {"F", "..-."},
            {"G", "--."},
            {"H", "...."},
            {"I", ".."},
            {"J", ".---"},
            {"K", "-.-"},
            {"L", ".-.."},
            {"M", "--"},
            {"N", "-."},
            {"O", "---"},
            {"P", ".--."},
            {"Q", "--.-"},
            {"R", ".-."},
            {"S", "..."},
            {"T", "-"},
            {"U", "..-"},
            {"V", "...-"},
            {"W", ".--"},
            {"X", "-..-"},
            {"Y", "-.--"},
            {"Z", "--.."},
            {"0", "-----"},
            {"1", ".----"},
            {"2", "..---"},
            {"3", "...--"},
            {"4", "....-"},
            {"5", "....."},
            {"6", "-...."},
            {"7", "--..."},
            {"8", "---.."},
            {"9", "----."},
            {".", ".-.-.-"},
            {":", "---..."},
            {",", "--..--"},
            {";", "-.-.-."},
            {"?", "..--.."},
            {"=", "-...-"},
            {"'", ".----."},
            {"/", "-..-."},
            {"!", "-.-.--"},
            {"-", "-....-"},
            {"_", "..--.-"},
            {"\"", ".-..-."},
            {"(", "-.--."},
            {")", "-.--.-"},
            {"$", "...-..-"},
            {"&", "...."},
            {"@", ".--.-."}
    };
    return encode_table;
}


std::map<string, string> make_decode_table() {
    static bool inited = false;
    static std::map<string, string> table;
    if (inited) return table;
    for (auto const& kv : make_encode_table())
        table[kv.second] = kv.first;
    inited = true;
    return table;
}

void replace_char(string &str, char src, char tgt) {
    for (char & i : str) {
        if (i == src)
            i = tgt;
    }
}

std::vector<string> split_by(string const& str, char break_by) {
    std::vector<string> parts;
    uint i = 0, j = 0;
    for (; j < str.size(); ++j) {
        if (str[j] != break_by) continue;
        if (i != j) {
            parts.push_back(str.substr(i, j-i));
            i = j+1;
        }
    }
    if (i != j)
        parts.push_back(str.substr(i, j-i));
    return parts;
}

string decode(string &str, char break_by, char short_char, char long_char) {
    replace_char(str, short_char, '.');
    replace_char(str, long_char, '-');
    auto const parts = split_by(str, break_by);

    auto const& decode_table = make_decode_table();
    string decoded_str;
    for (auto const& part : parts) {
        try {
            decoded_str.append(decode_table.at(part));
        } catch (std::out_of_range& e) {
            cout << e.what() << std::endl;
            cout << "while processing: " << part << std::endl;
        }
    }

    return decoded_str;
}

string encode(string const& str) {
    return "";
}