#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
    std::string::size_type end = s.length();
    std::string::size_type start = 0;

    if (start == end) {
        return true;
    }
    if (s[start] != s[end - 1]) {
        return false;
    }

    if (start + 2 < end) {
        std::string::size_type new_start = 1;
        std::string::size_type new_end = s.length() - 2;
        s = s.substr(new_start, new_end);
        return palindrome_recursive(s);
    }
    return true;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
