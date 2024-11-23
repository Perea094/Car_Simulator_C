#include <iostream>
#include <thread>   // Para std::this_thread::sleep_for
#include <chrono>   // Para std::chrono::milliseconds
#include <cstdlib>  // Para system("clear") o system("cls")
#include <conio.h>  // Para _kbhit() y _getch() en Windows
#include <string>


const int FILAS = 5;    // Número de carriles
const int COLUMNAS = 30;  // Longitud de la pista
const float ObstacleProbability = 5; // Probabilidad de que se genere un obstáculo
const float GalonProbability = 1.5;
const float ObstacleProbability2 = 3;
const std::string CarColor1 = "\033[31;40m";
const std::string DEFAULT = "\033[0m";
const std::string ObstacleColor1 = "\033[33;40m";
const std::string ObstacleColor2 = "\033[37;40m";
const std::string TrackColor1 = "\033[37;40m";
const std::string GalonesColor = "\033[32;40m";

const std::string Car1 = CarColor1 + "C";
const std::string Obstacle1 = ObstacleColor1 + "#";
const std::string Obstacle2 = ObstacleColor2 + "x";
const std::string Path = TrackColor1 + "-";
const std::string Galones = GalonesColor + "+";

int CarIntegrity = 100;

std::string difficultyName = "Normal";
float difficulty = 2;
int gameSpeed = 100 * difficulty;
bool progressiveDif = true;

int combustible = 100;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}

int RangedRandInt(int range_min, int range_max)
{
    float r = (static_cast<double>(rand()));
    // Generate random numbers in the interval [range_min, range_max], inclusive.
    float r1 = (static_cast<double>(rand())/RAND_MAX) * (range_max - range_min) + range_min;
    return r1;
}

void inicializarPista(std::string pista[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            pista[i][j] = Path;  // Inicializa la pista con '-'
        }
    }
}

void generarObstaculos(std::string pista[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        if (RangedRandInt(0,100) < ObstacleProbability) {  // Genera un obstáculo con probabilidad 
            pista[RangedRandInt(0,5)][COLUMNAS - 1] = Obstacle1;
        }
        if (RangedRandInt(0,100) < GalonProbability) {  // Genera un obstáculo con probabilidad 
            pista[i][COLUMNAS - 1] = Galones;
            }
        if (RangedRandInt(0,100) < ObstacleProbability2) {  // Genera un obstáculo con probabilidad 
            pista[i][COLUMNAS - 1] = Obstacle2;
            }
    }
}


void moverObstaculos(std::string pista[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 1; j++) {
            pista[i][j] = pista[i][j + 1];  // Desplaza los obstáculos hacia la izquierda
        }
        pista[i][COLUMNAS - 1] = Path;  // Vacía la última columna
    }
}

void dibujarPista(std::string pista[FILAS][COLUMNAS], int carCoordY, int carCoordX) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == carCoordY && j == carCoordX) {
                std::cout << Car1;  // Dibuja el coche en su posición
            } else {
                std::cout <<pista[i][j];
            }
        }
        std::cout << std::endl;
    }
}

bool detectarColision(std::string pista[FILAS][COLUMNAS], int carCoordY, int carCoordX) {
    return pista[carCoordY][carCoordX] == Obstacle1;  // Si hay un obstáculo en la posición del coche
}

bool detectarGalon(std::string pista[FILAS][COLUMNAS], int carCoordY, int carCoordX) {
    return pista[carCoordY][carCoordX] == Galones;  // Si hay un galón
}

bool detectarColision2(std::string pista[FILAS][COLUMNAS], int carCoordY, int carCoordX) {
    return pista[carCoordY][carCoordX] == Obstacle2;  // Si hay un obstaculo 2
}

void printSpeed(int& velocimeter){
    float maxSpeed = (2 * 100 * difficulty) - (difficulty * 80) - gameSpeed;
    std::cout << "Velocidad: " << velocimeter << "km/h" << std::endl;
    if (velocimeter <= maxSpeed) {velocimeter++;};
};

int detectarPuntuacion(std::string pista[][COLUMNAS]) {
    int puntajeAsumar = 0; // Inicializar fuera del bucle
    for (int i = 0; i < FILAS; i++) {
        if (pista[i][0] == Obstacle1) {
            puntajeAsumar++;
        }
    }
    return puntajeAsumar; // Devolver el puntaje acumulado
}

void jugar() {
    
    std::string pista[FILAS][COLUMNAS];
    int carCoordY = FILAS / 2;  // Posición inicial del coche en el carril del medio
    int carCoordX = 0;          // Posición inicial en la columna 0
    int puntaje = 0;
    int velocimeter = 10;
    bool jugando = true;

    limpiarPantalla();
    inicializarPista(pista);

    while (jugando && combustible >= 0 && CarIntegrity > 0) {
        limpiarPantalla();

        // Generar y mover obstáculos
        generarObstaculos(pista);
        moverObstaculos(pista);

        // Detectar colisión
        if (detectarColision(pista, carCoordY, carCoordX)) {
            std::cout << "Chocaste! Fin del juego..." << std::endl;
            // Mostrar puntaje final
            std::cout << "Puntaje final: " << puntaje << std::endl;
            break;
        }

        if (detectarColision2(pista,carCoordY, carCoordX)) {
            CarIntegrity -=25;
            pista[carCoordY][carCoordX] = Path;
        }

        if (detectarGalon(pista, carCoordY, carCoordX)){
            if (CarIntegrity < 100) {CarIntegrity += 10;}
            combustible += 20;
            pista[carCoordY][carCoordX] = Path;
        }

        puntaje += detectarPuntuacion(pista);
        // Incrementar puntaje si el coche esquiva obstáculos en la primera columna
        if (pista[carCoordY][0] == Path || pista[carCoordY][0] == Obstacle1) {
            puntaje++;
        }

        //std::cout << DEFAULT << "Simulador de autos" << std::endl;
        std::cout << "==============================" << std::endl;
        // Dibujar la pista, el coche y mostrar estadísticas
        dibujarPista(pista, carCoordY, carCoordX);
        std::cout << DEFAULT;
        std::cout << "==============================" << std::endl;
        std::cout << "Integridad del Coche: " << CarIntegrity << "%" << std::endl;
        std::cout << "Combustible: " << combustible << "%" << std::endl;
        printSpeed(velocimeter);
        std::cout << "Puntaje: " << puntaje << std::endl;
        

        // Control del coche (interacción)
        if (_kbhit()) {  // Si se presiona una tecla
            char tecla = _getch();
            if ((tecla == 'w'||tecla == 'W') && carCoordY > 0) {
                carCoordY--;  // Subir carril
            } else if ((tecla == 's'||tecla == 'S') && carCoordY < FILAS - 1) {
                carCoordY++;  // Bajar carril
            } else if ((tecla == 'a'||tecla == 'A') && carCoordX > 0) {
                carCoordX--;  // Mover a la izquierda
            } else if ((tecla == 'd'||tecla == 'D') && carCoordX < COLUMNAS - 3) {
                carCoordX++;  // Mover a la derecha
            }
        }

        if (progressiveDif && gameSpeed > 10) {
            gameSpeed--;};
        
        // Reducir combustible
        combustible--;

        // Pausa para simular tiempo real
        std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed));
    }
    if (CarIntegrity < 0) {std::cout << "\nTu coche ya no funciona!\nFin del juego...\n";}
    if (combustible < 0) {
        std::cout << "\nNo tienes combustible!\nFin del juego..." << std::endl;
    }
}

int gameMenu(){
    std::string menuLine = "\n==============================\n";
    std::cout << menuLine << "\tWelcome to the \n    Car Racing Simulator!!" << menuLine;
    std::string userChoice = "☺";
    while (true) {
        std::cout << "Select an option...\n 1) Start Game!\n 2) Set Difficulty\n 3) Personalization\n 4) Exit\n ";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {return 1;}
        else if (userChoice == "2") {return 2;}
        else if (userChoice == "3") {return 3;}
        else if (userChoice == "4") {break;}
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
        else if (userChoice == "3") {return 4;}
        else {std::cout << "No valid option\n";};
    };
    //return 0;
};

int gameDifficultyMenu(){
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) Easy\n 2) Normal ";
        std::cout << "\n 3) Hard\n 4) Demon\n 5)Back to difficulty Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {difficulty = 5; difficultyName = "Easy"; return 2;}
        else if (userChoice == "2") {difficulty = 2; difficultyName = "Normal"; return 2;}
        else if (userChoice == "3") {difficulty = 1; difficultyName = "Hard";return 2;}
        else if (userChoice == "4") {difficulty = 0.1; difficultyName = "Demon"; return 2;}
        else if (userChoice == "5") {return 2;}
        else {std::cout << "No valid option\n";};
    };
    return 1;
}

int gasolineMenu() {
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) 50 %\n 2) 100 %";
        std::cout << "\n 3) 200\n 4) Inf\n 5)Back to difficulty Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {combustible = 50; return 2;}
        else if (userChoice == "2") {combustible = 100; return 2;}
        else if (userChoice == "3") {combustible = 200; return 2;}
        else if (userChoice == "4") {combustible = 999999999; return 2;}
        else if (userChoice == "5") {return 2;}
        else {std::cout << "No valid option\n";};
    };
    return 1; 
}


int difficultyMenu(){
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) Game Difficulty: " << difficultyName << "\n 2) Progressive Difficulty: " << progressiveDif;
        std::cout << "\n 3) Gasoline: " <<  combustible <<" %\n 4) Back to Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {
            int userChoice2 = gameDifficultyMenu();
            return userChoice2;}
        else if (userChoice == "2") {progressiveDif = !progressiveDif; return 2;}
        else if (userChoice == "3") {
            int userChoice3 = gasolineMenu();
            return userChoice3;
        }
        else if (userChoice == "4") {return 5;}
        else {std::cout << "No valid option\n";};
    };
    return 1;
}

int personalizationMenu() {
    std::string userChoice;
    while (true) {
        std::cout << "\nSelect an option...\n 1) Car: " << Car1 << DEFAULT << "\n 2) Obstacles";
        std::cout << "\n 3) Track\n 4) Back to Menu\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {return 3;}
        else if (userChoice == "2") {return 3;}
        else if (userChoice == "3") {return 3;}
        else if (userChoice == "4") {return 5;}
        else {std::cout << "No valid option\n";};
    };
    return 1;
}

int main() {
    std::srand(static_cast<unsigned>(time(0)));  // Inicializa la semilla para los obstáculos
    int menuSelection = gameMenu();

    while (true)
    {
        if (menuSelection == 1) {jugar(); menuSelection = replayMenu();}
        else if (menuSelection == 2) {menuSelection = difficultyMenu();}
        else if (menuSelection == 3) {menuSelection = personalizationMenu();}
        else if(menuSelection == 5) {menuSelection = gameMenu();}
        else {std::cout << "Quiting Game...";break; return 0;}
        
    };

    return 0;
}

// alt 1 ☺  alt 2 ☻  alt 3 ♥ ♦ ♣ ♠ 6
// alt 7 • ◘○◙♂♀♪♫☼►◄↕‼¶§▬ 22
// alt 23 ↨↑↓↓→←∟↔▲▼

// alt 127 ⌂ ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®
// alt 170 ¬½¼¡«»░▒▓│┤ÁÂÀ©╣║╗╝¢¥┐└┴┬├─┼ãÃ╚╔╩╦╠═╬¤ðÐÊËÈıÍÎ
//alt 216 Ï┘┌█▄¦Ì▀ÓßÔÒõÕµþÞÚÛÙýÝ¯´­­­­
// alt 241 ±‗¾¶§÷¸°¨·¹³²■ 
// 