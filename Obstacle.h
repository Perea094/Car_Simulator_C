#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "EntityProperties.h"

class Obstacle
{
    private:
        std::string ObstacleType;
        float ObstacleIntegrity = 1;

    public:
        void set_ObstacleType(std::string);
        std::string get_ObstacleType();

        EntityProperties ObstacleProperties;

        bool check_integrity(bool);
};

#endif