#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void print() const;
    void set_credit_limit(int raja);
    void save_money(int maara);
    void take_money(int maara);
    void transfer_to(Account, int maara);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    std::string owner_;
    bool has_credit_;
    std::string iban_;
    int credit_limit;
    int saved_money;
    // More attributes/methods
};

#endif // ACCOUNT_HH
