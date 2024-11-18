#include "Obstacle.h"

void Obstacle::set_ObstacleType(std::string type){ObstacleType = type;}
std::string Obstacle::get_ObstacleType(){return ObstacleType;}

bool Obstacle::check_integrity(bool condition)
{
    if (condition)
    {
        ObstacleIntegrity = ObstacleIntegrity - 10;
    }
    return ObstacleIntegrity == 1;
}

