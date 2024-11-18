#include "Car.h"

void Car::set_CarName(std::string name){CarName = name;};
std::string Car::get_CarName(){return CarName;}

bool Car::check_integrity(bool condition) 
{
    if (condition) 
    {
        CarIntegrity = CarIntegrity - 25;

        return CarIntegrity > 0.0; 
    }
    return true;
}
