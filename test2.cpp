#include <iostream>
#include <string>

#define RED "\033[41m"
#define RESET "\033[0m"

const std::string RED1 = "\033[41m";
const std::string DEFAULT = "\033[0m";
const std::string Color = "\033[34m";
const std::string Color2 = "\e[0;101m";

int main() {
    std::cout << DEFAULT;
    std::cout << Color2 << "Viernes 13 A Color"<<std::endl;
    //std::cout << RED1 << "Hola Mundo" << DEFAULT << "Adios Mundo" << std::endl;
    int mun1;
    std::cout << DEFAULT;
    //std::cout << RED << "Este texto es rojo" << RESET << std::endl;

    //std::cout << "\251  " << std::endl;
    //std::cin>>mun1;

    // Código ANSI para texto blanco (37) sobre fondo rojo (41)
    std::cout << "\033[37;41m" << "Texto blanco sobre fondo rojo" << "\033[0m" << std::endl;
    // Código ANSI para texto negro (30) sobre fondo amarillo (43)
    std::cout << "\033[30;43m" << "Texto negro sobre fondo amarillo" << "\033[0m" << std::endl;
    
    return 0;
}
