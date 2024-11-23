#ifndef GAME_H
#define GAME_H

#include "Car.h"
#include "Track.h"
#include "Obstacle.h"

class Game
{
    private:
        std::string diffName;

        float difficulty; // Dificultad, determina el gameSpeed
        int score;
        static const int max_obstacles = 4; // Cantidad Máxima de objetos obstáculo
        
        int gameSpeed; // El tick del juego (Cada cuanto se reinicia la pantalla)
        
        bool progressiveDiff; // Habilita o no la dificultad progresiva
        bool gameState;
        
        Car CarInGame; // Coche manjeado por el jugador
        Track TrackInGame; // Pista en la que corre el coche
        Obstacle ObstaclesInGame[max_obstacles]; // Obstaculos o entidades del juego

    public:
        // Constructor
        Game();
        
        // Setters
        void setDifficulty(float);
        void setGameSpeed (int);
        void setProgressiveDiff(bool);
        void setGameSate(bool);
        void setCarInGame(const Car&);
        void setTrackInGame(const Track&);
        void setObstacleInGame(const Obstacle&, int);
        void setScore(int);
        void setDiffName(const std::string&);

        
        // Getters
        std::string getDiffName() const;

        int getMax_Obstacles() const;
        int getScore() const;
        float getDifficulty() const;

        int getGameSpeed() const;

        bool getProgressiveDiff() const;
        bool getGameState() const;


        const Car& getCarInGame() const;
        const Track& getTrackInGame() const;
        const Obstacle& getObstacleInGame(int ) const;
};


#endif