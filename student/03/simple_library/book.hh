#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>
#include "date.hh"

class Book
{
public:
    Book(const std::string& author, const std::string& name);
    void print();
    void renew();
    void give_back();
    void loan(const Date &date);

private:
    std::string author_;
    std::string name_;
    Date date_;
    Date return_date;
    bool available_;

};

#endif // BOOK_HH
