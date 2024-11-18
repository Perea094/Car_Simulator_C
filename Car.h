#ifndef CAR_H
#define CAR_H

#include "EntityProperties.h"

class Car
{
    private:
        std::string CarName;
        std::string CarDirection;
        float CarIntegrity = 100;
    public:
        void set_CarName(std::string);
        std::string get_CarName();

        EntityProperties CarProperties;

        bool check_integrity(bool);
};


#endif