#include "Car.h"

// Constructo por defecto
Car::Car()
    : EntityProperties("C","31","Car","40"), integrity(100), fuel(100) {}

// Constructor parametrizado
Car::Car(const std::string& shape, const std::string& color, const std::string& name, 
         const std::string& background, float integrity)
    : EntityProperties(shape, color, name, background), integrity(integrity) {}

// Asigna el nuevo valor
void Car::setIntegrity(float newIntegrity) {integrity = newIntegrity;}
void Car::setFuel(int newFuel) {fuel = newFuel;}
void Car::setCoordY(int y) {coords[0] = y;}
void Car::setCoordX(int x) {coords[1] = x;}


// Devuelve el valor actual de integrity
float Car::getIntegrity() const {return integrity;}
int Car::getFuel() const {return fuel;}
int Car::getCoordY() const {return coords[0];}
int Car::getCoordX() const {return coords[1];}
