#ifndef MAMMAL_HH
#define MAMMAL_HH
#include "animal.hh"


class mammal: public Animal
{
public:
    mammal();
    void suckle(std::ostream& output);
};

#endif // MAMMAL_HH
