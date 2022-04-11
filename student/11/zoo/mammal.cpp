#include "mammal.hh"

mammal::mammal(): Animal("Kip kop kip kop")
{

}

void mammal::suckle(std::ostream &output)
{
    output << "Mus mus" << std::endl;
}
