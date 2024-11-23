#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "EntityProperties.h"

class Obstacle : public EntityProperties
{
    private:
        float damage; // Numero que afectara la integridad del coche
        float probability; // La probabilidad de que aparezca
        

    public:
        // Constructores
        Obstacle();
        Obstacle(const std::string&, const std::string&,
                const std::string&, const std::string&, float, float);

        // Setters
        void setDamage(float);
        void setProbability(float);

        // Getters
        float getDamage() const;
        float getProbability() const;

};

#endif