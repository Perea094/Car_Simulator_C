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
const std::string CarColor1 = "\033[31;40m";
const std::string DEFAULT = "\033[0m";
const std::string ObstacleColor1 = "\033[33;40m";
const std::string TrackColor1 = "\033[37;40m";
const std::string GalonesColor = "\033[32;40m";

const std::string Car1 = CarColor1 + "C";
const std::string Obstacle1 = ObstacleColor1 + "#";
const std::string Path = TrackColor1 + "-";
const std::string Galones = GalonesColor + "+";

float difficulty = 2;
/*int gameSpeedDeterminer(float diff){
    int speed = 100 * (diff);
    return speed;
};*/
int gameSpeed = 100 * difficulty;
const bool progressiveDif = true;


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
    int combustible = 100;
    int puntaje = 0;
    int velocimeter = 10;
    bool jugando = true;

    limpiarPantalla();
    inicializarPista(pista);

    while (jugando && combustible >= 0) {
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

        if (detectarGalon(pista, carCoordY, carCoordX)){
            combustible += 20;
            pista[carCoordY][carCoordX] = Path;
        }

        puntaje += detectarPuntuacion(pista);
        // Incrementar puntaje si el coche esquiva obstáculos en la primera columna
        if (pista[carCoordY][0] == Path || pista[carCoordY][0] == Obstacle1) {
            puntaje++;
        }

        std::cout << DEFAULT << "Simulador de autos" << std::endl;
        std::cout << "==============================" << std::endl;
        // Dibujar la pista, el coche y mostrar estadísticas
        dibujarPista(pista, carCoordY, carCoordX);
        std::cout << DEFAULT;
        std::cout << "==============================" << std::endl;
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

    if (combustible < 0) {
        std::cout << "No tienes combustible!\nFin del juego." << std::endl;
    }
}

int gameMenu(){
    std::string menuLine = "\n==============================\n";
    std::cout << menuLine << "\tWelcome to the \n    Car Racing Simulator!!" << menuLine;
    std::string userChoice = "☺";
    while (true) {
        std::cout << "Select an option...\n 1) Start Game!\n 2) Set Difficulty\n 3) Personalization\n 4) Exit\n";
        std::cin >> userChoice; std::cout << std::endl;
        if (userChoice == "1") {return 1;}
        else if (userChoice == "2") {return 2;}
        else if (userChoice == "3") {return 3;}
        else if (userChoice == "4") {break;}
        else {std::cout << "No valid option\n";};
    };
    return 0;
}

/*bool gameMenu1(){
    std::string menuLine = "\n==============================\n";
    std::cout << menuLine << "\tWelcome to the \n    Car Racing Simulator!!" << menuLine;
    std::string userChoice = "☺";
    while (userChoice != "y" && userChoice != "n")
    {
        std::cout << "Start? (y/n)\n"; std::cin >> userChoice; std::cout << std::endl;
    };
    if (userChoice == "y") {return true;}
        else {return false;};
    
}*/

bool replayMenu(){
    std::string userChoice = "☺";
    while (userChoice != "y" && userChoice != "n")
    {
        std::cout << "Replay? (y/n)\n"; std::cin >> userChoice; std::cout << std::endl;
    };
    if (userChoice == "y") {return true;}
        else {return false;};
};

int main() {
    std::srand(static_cast<unsigned>(time(0)));  // Inicializa la semilla para los obstáculos
    int menuSelection = gameMenu();

    while (true)
    {
        if (menuSelection == 1) {jugar();};

        menuSelection = replayMenu();
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