#include "Game.h"

// Constructor
Game::Game() : difficulty(1.0), gameSpeed(200), progressiveDiff(true), gameState(true), score(0), diffName("Normal"),  
               CarInGame(Car()), TrackInGame(Track()) ,ObstaclesInGame() {}

// Setters
void Game::setDifficulty(float newDifficulty) {difficulty = newDifficulty;}

void Game::setGameSpeed(int newGameSpeed) {gameSpeed = newGameSpeed;}

void Game::setProgressiveDiff(bool newProgressiveDiff) {progressiveDiff = newProgressiveDiff;}

void Game::setGameSate(bool newGameState) {gameState = newGameState;}

void Game::setCarInGame(const Car& newCar) {CarInGame = newCar;}

void Game::setTrackInGame(const Track& newTrack) {TrackInGame = newTrack;}

void Game::setObstacleInGame(const Obstacle& newObstacle, int index) {ObstaclesInGame[index] = newObstacle;}

void Game::setScore(int newScore) {score = newScore;}

void Game::setDiffName(const std::string& newName) {diffName = newName;}

// Getters
std::string Game::getDiffName() const {return diffName;}

int Game::getMax_Obstacles() const {return max_obstacles;}
float Game::getDifficulty() const {return difficulty;}
int Game::getScore() const {return score;}


int Game::getGameSpeed() const {return gameSpeed;}

bool Game::getProgressiveDiff() const {return progressiveDiff;}
bool Game::getGameState() const {return gameState;}

const Car& Game::getCarInGame() const {return CarInGame;}
const Track& Game::getTrackInGame() const {return TrackInGame;}
const Obstacle& Game::getObstacleInGame(int index) const {return ObstaclesInGame[index];}