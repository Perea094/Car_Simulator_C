
#include <iostream>
#include <string>



int main(){
    const std::string ansiPart1 = "\e[";
    std::string ansiColor = "0";
    std::string ansiBackground = "";
    std::string ansiCommand = ansiPart1 + ansiBackground + ";" + ansiColor + "m";
    std::cout << ansiCommand + "Old text\n";
    std::cin >> ansiColor;
    std::cin >> ansiBackground;
    ansiCommand = ansiPart1 + ansiBackground + ";" + ansiColor + "m";
    std::cout << ansiCommand + "New text\e[0m\n";

}

