#include "Game.h"
#include "Car.h"
#include "Track.h"
#include "Obstacle.h"
#include "EntityProperties.h"


#include "Game.cpp"
#include "Car.cpp"
#include "Track.cpp"
#include "Obstacle.cpp"
#include "EntityProperties.cpp"

#include <iostream> // Para imprimir en la terminal
#include <thread>   // Para std::this_thread::sleep_for (duerme el código)
#include <chrono>   // Para std::chrono::milliseconds (tiempo)
#include <cstdlib>  // Para system("clear") o system("cls") (borra la terminal)
#include <conio.h>  // Para _kbhit() y _getch() en Windows (Obtiene teclas)
#include <string>
#include <vector>
#include <random>

#define DEFAULT "\e[0m"



// Resetea la Terminal cada vez que es llamada
void refreshTerminal() 
{
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}

int RangedRandInt(int range_min, int range_max)
{
    float r = (static_cast<double>(rand())); // Eliimina el primer numero aleatorio
    // Generate random numbers in the interval [range_min, range_max].
    float r1 = (static_cast<double>(rand())/RAND_MAX) * (range_max - range_min) + range_min;
    return r1;
}

std::string repeatString(const std::string& str, int times) {
    std::string result;
    for (int i = 0; i < times; ++i) {
        result += str;
    }
    return result;
}

void initializeTrack(std::vector<std::vector<std::string>>& grid, std::string Path) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] = Path;  // Inicializa la pista con el valor Path
        }
    }
}


void generateEntyties(std::vector<std::vector<std::string>>& grid, Obstacle Obstacle1, Obstacle Obstacle2, Obstacle Obstacle3, Obstacle Obstacle4) {
    for (int i = 0; i < grid.size(); i++) {
        if (RangedRandInt(0,100) < Obstacle1.getProbability()) {  // Genera un obstáculo con probabilidad 
            grid[RangedRandInt(0,5)][grid[i].size() - 1] = Obstacle1.getFinalShape();
        }
        if (RangedRandInt(0,100) < Obstacle2.getProbability()) {  
            grid[i][grid[i].size() - 1] = Obstacle2.getFinalShape();
            }
        if (RangedRandInt(0,100) < Obstacle3.getProbability()) {  
            grid[i][grid[i].size() - 1] = Obstacle3.getFinalShape();
            }
        if (RangedRandInt(0,100) < Obstacle4.getProbability()) {  
            grid[i][grid[i].size() - 1] = Obstacle4.getFinalShape();
            }
    }
}

void moveEntyties(std::vector<std::vector<std::string>>& grid, std::string Path) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size() - 1; j++) {
            grid[i][j] = grid[i][j + 1];  // Desplaza los obstáculos hacia la izquierda
        }
        grid[i][grid[i].size() - 1] = Path;  // Vacía la última columna
    }
}

void printTrack(std::vector<std::vector<std::string>>& grid, int carCoordY, int carCoordX, std::string Car1) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (i == carCoordY && j == carCoordX) {
                std::cout << Car1;  // Dibuja el coche en su posición
            } else {
                std::cout <<grid[i][j];
            }
        }
        std::cout << std::endl;
    }
}

bool detectColision(std::vector<std::vector<std::string>>& grid, int carCoordY, int carCoordX, Obstacle tempObstacle) {
    return grid[carCoordY][carCoordX] == tempObstacle.getFinalShape();  // Si hay un obstáculo en la posición del coche
}

void printSpeed(int& velocimeter, Game tempGame){
    float maxSpeed = (2 * 100 * tempGame.getDifficulty()) - (tempGame.getDifficulty() * 80) - tempGame.getGameSpeed();
    std::cout << "Speed: " << velocimeter << "km/h" << std::endl;
    if (velocimeter <= maxSpeed) {velocimeter++;};
};

int detectScore(std::vector<std::vector<std::string>>& grid, std::string path) {
    int puntajeAsumar = 0; // Inicializar fuera del bucle
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i][0] != path) {
            puntajeAsumar++;
        }
    }
    return puntajeAsumar; // Devolver el puntaje acumulado
}

void play( Game& CarSimulator) 
{
    Track track1 = CarSimulator.getTrackInGame();
    Car car1 = CarSimulator.getCarInGame();
    Obstacle Obs11 = CarSimulator.getObstacleInGame(0); 
    Obstacle Obs22 = CarSimulator.getObstacleInGame(1); 
    Obstacle Obs33 = CarSimulator.getObstacleInGame(2); 
    Obstacle Obs44 = CarSimulator.getObstacleInGame(3); 


    const int ROWS = track1.getLanes();
    const int COLUMNS = track1.getLength();
    std::vector<std::vector<std::string>> grid(ROWS, std::vector<std::string>(COLUMNS));
    int carCoordY = ROWS / 2;  // Posición inicial del coche en el carril del medio
    int carCoordX = 0;          // Posición inicial en la columna 0
    car1.setCoordY(carCoordY); car1.setCoordX(carCoordX);
    int velocimeter = 10;
    std::string path = track1.getFinalTrackShape();
    

    refreshTerminal();
    initializeTrack(grid, path);
    

    while (CarSimulator.getGameState() && car1.getFuel() >= 0 && car1.getIntegrity() > 0) {
        refreshTerminal();

        // Generar y mover obstáculos
        generateEntyties(grid, Obs11, Obs22, Obs33, Obs44);
        moveEntyties(grid, track1.getFinalTrackShape());
        

        // Detectar colisión
        if (detectColision(grid, car1.getCoordY(), car1.getCoordX(), Obs11)) {
            std::cout << "Chocaste! Fin del juego..." << std::endl;
            break;
        }

        if (detectColision(grid, car1.getCoordY(), car1.getCoordX(), Obs22)) {
            car1.setIntegrity(car1.getIntegrity() + Obs22.getDamage());
            grid[car1.getCoordY()][car1.getCoordX()] = path;
        }

        if (detectColision(grid, car1.getCoordY(), car1.getCoordX(), Obs33)){
            if (car1.getIntegrity() < 100) {
                car1.setIntegrity(car1.getIntegrity() + Obs33.getDamage());}
            car1.setFuel(car1.getFuel() + 20);
            grid[car1.getCoordY()][car1.getCoordX()] = path;
        }

        if (detectColision(grid, car1.getCoordY(), car1.getCoordX(), Obs44))
        {
            car1.setIntegrity(car1.getIntegrity() + Obs44.getDamage());
            grid[car1.getCoordY()][car1.getCoordX()] = path;
        }
        // Incrementar puntaje si el coche esquiva obstáculos en la primera columna
        CarSimulator.setScore(CarSimulator.getScore() + detectScore(grid, path));
        if (grid[car1.getCoordY()][0] == path || (grid[car1.getCoordY()][0] != path && grid[car1.getCoordY()][0] != Obs33.getFinalShape())) {
            CarSimulator.setScore(CarSimulator.getScore() + 1);
        }
        std::string wall = track1.getFinalWallsShape();
        std::string walls = repeatString(wall, track1.getLength());
        //std::cout << DEFAULT << "Simulador de autos" << std::endl;
        std::cout << walls << std::endl;
        // Dibujar la grid, el coche y mostrar estadísticas
        printTrack(grid, car1.getCoordY(), car1.getCoordX(), car1.getFinalShape());
        std::cout << walls << DEFAULT << std::endl;
        std::cout << "Car Integrity: " << car1.getIntegrity() << "%" << std::endl;
        std::cout << "Fuel: " << car1.getFuel() << "%" << std::endl;
        printSpeed(velocimeter, CarSimulator);
        std::cout << "Puntaje: " << CarSimulator.getScore() << std::endl;
        

        // Control del coche (interacción)
        if (_kbhit()) 
        {  
            char tecla = _getch(); // Si se presiona una tecla
            if ((tecla == 'w'||tecla == 'W') && carCoordY > 0) // Subir carril
            {car1.setCoordY(car1.getCoordY() - 1); } 
            else if ((tecla == 's'||tecla == 'S') && carCoordY < ROWS - 1) // Bajar carril
            {car1.setCoordY(car1.getCoordY() + 1);} 
            else if ((tecla == 'a'||tecla == 'A') && carCoordX > 0) // Mover a la izquierda
            {car1.setCoordX(car1.getCoordX() - 1);} 
            else if ((tecla == 'd'||tecla == 'D') && carCoordX < COLUMNS - 3)  // Mover a la derecha
            {car1.setCoordX(car1.getCoordX() + 1);}
        }

        if (CarSimulator.getProgressiveDiff() && CarSimulator.getGameSpeed() > 10) 
        {CarSimulator.setGameSpeed(CarSimulator.getGameSpeed() - 1);};
        
        // Reducir combustible
        car1.setFuel(car1.getFuel() - 1);

        // Pausa para simular tiempo real
        std::this_thread::sleep_for(std::chrono::milliseconds(CarSimulator.getGameSpeed()));
    }
    if (car1.getIntegrity() < 0) {std::cout << "\nTu coche ya no funciona!\nFin del juego...\n";}
    if (car1.getFuel() < 0) {
        std::cout << "\nNo tienes combustible!\nFin del juego..." << std::endl;
    }
    // Mostrar puntaje final
    std::cout << "Puntaje final: " << CarSimulator.getScore() << std::endl;
}

int gameMenu(){
    std::string menuLine = "\n==============================\n";
    std::cout << DEFAULT << menuLine << "\tWelcome to the \n    Car Racing Simulator!!" << menuLine;
    std::string userChoice = "☺";
    while (true) {
        std::cout << "Select an option...\n 1) Start Game!\n 2) Set Difficulty\n 3) Personalization\n 4) Info / Keys\n 5) Exit\n ";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {return 1;}
        else if (userChoice == "2") {return 2;}
        else if (userChoice == "3") {return 3;}
        else if (userChoice == "4") {return 4;}
        else if (userChoice == "5") {return 0; break;}
        else {std::cout << "No valid option\n";};
    };
    return 0;
}

int replayMenu(){
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) Retry!\n 2) Menu\n 3) Exit\n ";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {return 1;}
        else if (userChoice == "2") {return 5;}
        else if (userChoice == "3") {return 0;}
        else {std::cout << "No valid option\n";};
    };
};

int gameDifficultyMenu(Game& tempGame){
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) Easy\n 2) Normal ";
        std::cout << "\n 3) Hard\n 4) Demon\n 5)Back to difficulty Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") { tempGame.setDifficulty(5); tempGame.setDiffName("Easy"); return 2;}
        else if (userChoice == "2") {tempGame.setDifficulty(2); tempGame.setDiffName("Normal"); return 2;}
        else if (userChoice == "3") {tempGame.setDifficulty(1); tempGame.setDiffName("Hard");return 2;}
        else if (userChoice == "4") {tempGame.setDifficulty(0.1); tempGame.setDiffName("Demon"); return 2;}
        else if (userChoice == "5") {return 2;}
        else {std::cout << "No valid option\n";};
    };
    return 1;
}

int gasolineMenu(Car& tempCar) {
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) 50 %\n 2) 100 %";
        std::cout << "\n 3) 200\n 4) Inf\n 5)Back to difficulty Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {tempCar.setFuel(50); return 2;}
        else if (userChoice == "2") {tempCar.setFuel(100); return 2;}
        else if (userChoice == "3") {tempCar.setFuel(200); return 2;}
        else if (userChoice == "4") {tempCar.setFuel(9999999); return 2;}
        else if (userChoice == "5") {return 2;}
        else {std::cout << "No valid option\n";};
    };
    return 1; 
}

int difficultyMenu(Game& tempGame, Car& tempCar){
    std::string userChoice;
    while (true) {
        std::cout << "Select an option...\n 1) Game Difficulty: " << tempGame.getDiffName();
        std::cout << "\n 2) Progressive Difficulty: " << (tempGame.getProgressiveDiff() ? "True":"False");
        std::cout << "\n 3) Gasoline: " <<  tempCar.getFuel() <<" %\n 4) Back to Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {
            int userChoice2 = gameDifficultyMenu(tempGame);
            return userChoice2; continue;}
        else if (userChoice == "2") {tempGame.setProgressiveDiff(!tempGame.getProgressiveDiff()); return 2; continue;}
        else if (userChoice == "3") {
            int userChoice3 = gasolineMenu(tempCar);
            return userChoice3; continue;
        }
        else if (userChoice == "4") {return 5; continue;}
        else {std::cout << "No valid option\n"; continue;};
    };
    return 1;
}

int carPersonalizationMenu(Car& tempCar) 
{
    std::string userChoice;
    while (userChoice.size() != 1) {
        std::cout << "Input a character...\n";
        std::cin >> userChoice;
    };
    tempCar.setShape(userChoice);
    return 3;
}

std::string customizableObstacle(Obstacle& tempObs4)
{
    std::string userChoice;
    while (true) 
    {
        std::cout << DEFAULT << "Select an option...\n 1) Shape: " << tempObs4.getFinalShape() 
        << DEFAULT << "\n 2) Probability: " << tempObs4.getProbability() << "%\n 3) Damage: " << -tempObs4.getDamage()
        << "\n 4) Back\n";
        std::cin >> userChoice;
        std::string newShape;
        float probInput;
        if (userChoice == "1") {std::cout << "Enter the desired shape\n"; std::cin >> newShape; tempObs4.setShape(newShape); }
        else if (userChoice == "2") {std::cout << "Enter the desired probability\n"; std::cin >> probInput; tempObs4.setProbability(probInput);}
        else if (userChoice == "3") {std::cout << "Enter the desired damage\n"; std::cin >> probInput; tempObs4.setDamage(probInput); }
        else if (userChoice == "4") {return "0"; break;}
    }
        

       
}

void obstaclePersonalizationMenu(Obstacle& tempObs1, Obstacle& tempObs2, Obstacle& tempObs3, Obstacle& tempObs4)
{
    std::string userChoice;
    while (true) 
    {
        std::cout << DEFAULT << "Select an option...\n 1) " << tempObs1.getName() << ": " << tempObs1.getFinalShape() << " " << DEFAULT 
        << tempObs1.getProbability() << "%" << "\n 2) "<< tempObs2.getName() << ": " << tempObs2.getFinalShape() << DEFAULT << " "
        << tempObs2.getProbability() << "%" << "\n 3) " << tempObs3.getName() << ": " << tempObs3.getFinalShape() << DEFAULT 
        << " " << tempObs3.getProbability() << "%"<< "\n 4) Customizable Obstacle: " << tempObs4.getFinalShape() << DEFAULT << "\n 5) Back\n";
        std::cin >> userChoice;
        float probInput;
        if (userChoice == "1") {std::cout << "Enter the desired probability: "; std::cin >> probInput; tempObs1.setProbability(probInput);}
        else if (userChoice == "2") {std::cout << "Enter the desired probability: "; std::cin >> probInput; tempObs2.setProbability(probInput);}
        else if (userChoice == "3") {std::cout << "Enter the desired probability: "; std::cin >> probInput; tempObs3.setProbability(probInput);}
        else if (userChoice == "4") {userChoice = customizableObstacle(tempObs4);}
        else if (userChoice == "5") {break;}  
    }
}

void trackPersonalizationMenu(Track& tempTrack, Obstacle& tempObs1, Obstacle& tempObs2, Obstacle& tempObs3, Obstacle& tempObs4)
{
    std::string userChoice;
    Track defaultTrack;
    Track trackOption1("Garden", "37", "42"," ", "37", "1;43", "=", 5, 30);
    Track trackOption2("Water Pool", "37", "46", " ", "30", "47", "=", 5, 30);
    while (true) 
    {
        std::cout << "\nSelect an option...\n 1) " << defaultTrack.getName()<< ": " << defaultTrack.getFinalWallsShape() << defaultTrack.getFinalTrackShape() << defaultTrack.getFinalWallsShape()  
                  << DEFAULT << "\n 2) " << trackOption1.getName()<< ": " << trackOption1.getFinalWallsShape() << trackOption1.getFinalTrackShape() << trackOption1.getFinalWallsShape() 
                  << DEFAULT << "\n 3) " << trackOption2.getName()<< ": " << trackOption2.getFinalWallsShape() << trackOption2.getFinalTrackShape() << trackOption2.getFinalWallsShape() 
                  << DEFAULT <<" \n 4) Back to Menu\n";
        std::cin >> userChoice;
        tempObs3.setColor("32");
        if (userChoice == "1") {tempTrack = defaultTrack;break;}
        else if (userChoice == "2") {tempObs3.setColor("30");tempTrack = trackOption1; break;}
        else if (userChoice == "3") {tempTrack = trackOption2; break;}
        else if (userChoice == "4") {break;}        
    }
    tempObs1.setBackground(tempTrack.getTrackBackground());
    tempObs2.setBackground(tempTrack.getTrackBackground());
    tempObs3.setBackground(tempTrack.getTrackBackground());
    tempObs4.setBackground(tempTrack.getTrackBackground());


}

int personalizationMenu(Car& tempCar, Game& tempGame, Obstacle& tempObs1, Obstacle& tempObs2, Obstacle& tempObs3, Obstacle& tempObs4, Track& tempTrack) 
{
    std::string userChoice;
    while (true) 
    {
        std::cout << "\nSelect an option...\n 1) Car: " << tempCar.getFinalShape() << DEFAULT;
        std::cout << "\n 2) Obstacles: " << tempObs1.getFinalShape()<< " " << tempObs2.getFinalShape() << " " 
                  << tempObs3.getFinalShape() << " " << tempObs4.getFinalShape() << DEFAULT;
        std::cout << "\n 3) Track: " << tempTrack.getName() << " " <<tempTrack.getFinalWallsShape() << tempTrack.getFinalTrackShape() << tempTrack.getFinalWallsShape()  
                  << DEFAULT << "\n 4) Back to Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {carPersonalizationMenu(tempCar);}
        else if (userChoice == "2") {obstaclePersonalizationMenu(tempObs1, tempObs2, tempObs3, tempObs4);}
        else if (userChoice == "3") {trackPersonalizationMenu(tempTrack, tempObs1, tempObs2, tempObs3, tempObs4); return 3;}
        else if (userChoice == "4") {return 5;}
        else {std::cout << "No valid option\n";};
    };
    return 1;
}

int infoMenu(Obstacle& tempObs1, Obstacle& tempObs2, Obstacle& tempObs3, Obstacle& tempObs4) 
{
    std::string understood;
    std::cout << "Move UP (w)\nMove DOWN (s)\nMove RIGHT (d)\nMove LEFT (a)\n";
    std::cout << "Avoid the obstacles (" << tempObs1.getFinalShape() << " " << tempObs2.getFinalShape() << DEFAULT <<")\n"
    << "Refill your fuel and HP (" << tempObs3.getFinalShape() << DEFAULT << ")\nContinue (any key)...";
    std::cin >> understood;
    return 5;
}
int main()
{

    std::srand(static_cast<unsigned>(time(0)));  // Inicializa la semilla para los obstáculos
    int menuSelection = gameMenu();
    Game CarSimulator;
    Track track;
    Car myCar;
    myCar.setBackground(track.getTrackBackground());
    Obstacle Obs1("#", "33", "Rocks", track.getTrackBackground(), -1000, 5), 
    Obs2("x", "37", "Holes", track.getTrackBackground(), -25, 3), 
    Obs3("+", "32", "Regen", track.getTrackBackground(), 10, 1.5), Obs4;
    while (true)
    {
        myCar.setBackground(track.getTrackBackground());
        CarSimulator.setTrackInGame(track);
        CarSimulator.setCarInGame(myCar);
        CarSimulator.setObstacleInGame(Obs1,0);
        CarSimulator.setObstacleInGame(Obs2,1);
        CarSimulator.setObstacleInGame(Obs3,2);
        CarSimulator.setObstacleInGame(Obs4,3);
        if (menuSelection == 1) {play(CarSimulator); menuSelection = replayMenu(); continue;}
        else if (menuSelection == 2) {menuSelection = difficultyMenu(CarSimulator, myCar); continue;}
        else if (menuSelection == 3) {menuSelection = personalizationMenu(myCar, CarSimulator, Obs1, Obs2, Obs3, Obs4, track); continue;}
        else if(menuSelection == 5) {menuSelection = gameMenu(); continue;}
        else if(menuSelection == 4) {menuSelection = infoMenu(Obs1, Obs2, Obs3, Obs4); continue;}
        else {std::cout << "Quiting Game...";break; return 0;}
        
    };

    return 0;  
}