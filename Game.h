#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Car.h"
#include "Track.h"
#include "Obstacle.h"

class Game
{
    private:
        int GameState;

    public:
        Car CarInGame;
        Track TrackInGame;
        std::vector<Obstacle> ObstaclesInGame;
        void start_game();
        void pause_game();
        void update_game();
        void end_game();

        bool check_collision(); 
};


#endif