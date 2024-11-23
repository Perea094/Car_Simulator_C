#include "Obstacle.h"

// Constructor por defecto
Obstacle::Obstacle()
    : EntityProperties(), damage(0), probability(0) {}

// Constructor parametrizado
Obstacle::Obstacle(const std::string& shape, const std::string& color, const std::string& name, 
                   const std::string& background, float damage, float probability)
    : EntityProperties(shape, color, name, background), damage(damage), probability(probability) {}

void Obstacle::setDamage(float newDamage) {damage = newDamage;}

void Obstacle::setProbability(float newProbability) {probability = newProbability;}

float Obstacle::getDamage() const {return damage;}

float Obstacle::getProbability() const {return probability;}