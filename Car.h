#ifndef CAR_H
#define CAR_H

#include "EntityProperties.h"

class Car : public EntityProperties
{
    private:
        int fuel;
        int coords[2];

        float integrity; // Representa la integridad del coche
    public:
        // Constructores
        Car(); // Constructor por defecto
        Car(const std::string&, const std::string&,
            const std::string&, const std::string&, float);
        // Setters
        void setCoordX(int);
        void setCoordY(int);
        void setFuel(int);
        void setIntegrity(float);

        // Getters
        int getFuel() const;
        int getCoordX() const;
        int getCoordY() const;
        float getIntegrity() const;
};


#endif