#include <iostream>
#include <vector>
#include <cstdlib> // Para números aleatorios.
using namespace std;

class Entity 
{
    public:
    float EntityWidth;
    float EntityLenght;
    float EntitySpeed;
    string EntityColor;
    void update_position(){}
};
class Car : public Entity 
{
    public:
    string CarName;
    float CarXCoord;
    float CarYCoord;
    string CarDirection;
    float CarIntegrity;
    void move_left(){};
    void move_right(){};
    void accelerate(){};
    void decelerate(){};
    bool check_collision(){};
};

class Obstacle : public Entity 
{
    public:
    string ObstacleType;
    float ObstacleXCoord;
    float ObstacleYCoord;
    void move(){};
    bool detect_collision(){};
};


class Game 
{
    public:
    Car CarInGame;
    Track TrackInGame;
    Obstacle ObstaclesInGame;
    int GameState;
    int start_game(){};
    int pause_game(){};
    void update_game(){};
    int end_game(){};
};

class Track 
{
    public:
    string TrackName;
    float TrackFriction;
    string TrackColor;
    float TrackLimits;
    int TrackLanes;
    void change_track(){};
    bool detect_collision(){};
};

