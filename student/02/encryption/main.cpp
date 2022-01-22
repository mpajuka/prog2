#include <iostream>

using namespace std;

const int ASCII_MIN = 97;
const int ASCII_MAX = 122;
const int KEY_LENGTH = 26;

const std::string ERROR_ALPHABET = "Error! The encryption key must contain all alphabets a-z.";
const std::string ERROR_CASE = "Error! The encryption key must contain only lower case characters.";
const std::string ERROR_LENGTH = "Error! The encryption key must contain 26 characters.";

bool check_alphabet(const std::string &key);
bool check_lower_case(const std::string &key);
bool check_length(const std::string &key);



int main()
{
    // lue syöte

    std::string key = "";
    std::string text = "";

    std::cout << "Enter the encryption key: ";
    std::getline(std::cin, key);

    // testaa avain

    if(!check_length(key) or
       !check_lower_case(key) or
       !check_alphabet(key))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool check_alphabet(const std::string &key) {
    for(uint c = ASCII_MIN; c <= ASCII_MAX; c++) {
        if(key.find(c) == std::string::npos) {
            std::cout << ERROR_ALPHABET << std::endl;
            return false;
        }
    }
    return true;
}
bool check_lower_case(const std::string &key) {
    for(uint i = 0; i < key.length(); i++) {
        char c = key.at(i);
        if(c < ASCII_MIN or c > ASCII_MAX) {
            std::cout << ERROR_CASE << std::endl;
            return false;
        }
    }
    return true;
}
bool check_length(const std::string &key) {
    if (key.length() != KEY_LENGTH) {
        std::cout << ERROR_LENGTH << std::endl;
        return false;
    }
    return true;
}
