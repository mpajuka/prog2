#include "book.hh"
#include "date.hh"
#include <iostream>
#include <string>



Book::Book(const std::string& author, const std::string& name):
    author_(author),
    name_(name),
    date_(Date()),
    return_date(Date()),
    available_(true)
{

}

void Book::print()
{
    std::cout << author_ << " : " << name_ << std::endl;
    if (available_)
    {
        std::cout << "- available" << std::endl;
        return;
    }
    std::cout << "- loaned: ";
    date_.print();
    std::cout << "- to be returned: ";
    return_date.print();
}

void Book::loan(const Date &date)
{
    if (!available_)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }
    date_ = date;
    return_date = date_;
    return_date.advance(28);
    available_ = false;
}

void Book::renew()
{
    if (available_)
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
    return_date.advance(28);
}

void Book::give_back()
{
    available_ = true;
}

