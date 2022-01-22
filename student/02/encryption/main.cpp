#include <iostream>

using namespace std;

const int ASCII_MIN = 97;
const int ASCII_MAX = 122;
const int KEY_LENGTH = 26;

const std::string ERROR_ALPHABET = "Error! The encryption key must contain all alphabets a-z.";
const std::string ERROR_CASE = "Error! The encryption key must contain only lower case characters.";
const std::string ERROR_CASE_TEXT = "Error! the text to be encrypted must contain only lower case characters.";
const std::string ERROR_LENGTH = "Error! The encryption key must contain 26 characters.";

bool check_alphabet(const std::string &key);
bool check_lower_case(const std::string &key);
bool check_lower_case_text(const std::string &key);
bool check_length(const std::string &key);

std::string encryption(const std::string &key, std::string text);


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

    } else {
        std::cout << "Enter the text to be encrypted: ";
        std::getline(std::cin, text);

        if(!check_lower_case_text(text)) {
            return EXIT_FAILURE;
        }

        std::cout << "Encrypted text: " <<encryption(key, text) << std::endl;
        return EXIT_SUCCESS;

    }

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
bool check_lower_case_text(const std::string &key) {
    for(uint i = 0; i < key.length(); i++) {
        char c = key.at(i);
        if(c < ASCII_MIN or c > ASCII_MAX) {
            std::cout << ERROR_CASE_TEXT << std::endl;
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

std::string encryption(const std::string &key, std::string text) {
    for(uint i = 0; i < text.length(); i++)
    {
        char c_in_text = text.at(i);
        // eka kirjain c = 99
        // kirjaimen indeksi avaimessa
        // kirjaimen_ASCII - 97

        text.at(i) = key.at(c_in_text - ASCII_MIN);
    }
    return text;
}
