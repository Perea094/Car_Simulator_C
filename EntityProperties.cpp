#include "EntityProperties.h"

// Definimos el constructor predeterminado
EntityProperties::EntityProperties() 
    : shape("Z"), color("37"), name("undefined"), background("40") {}

// Definimos el constructor
EntityProperties::EntityProperties(const std::string& shape, const std::string& color, 
                                   const std::string& name, const std::string& background)
    : shape(shape), color(color), name(name), background(background) {}

//Method
std::string EntityProperties::getFinalShape() const
{
    const std::string ansiPart1 = "\e[";
    std::string ansiCommand = ansiPart1 + background + ";" + color + "m" + shape;
    return ansiCommand;
}

void EntityProperties::setShape(const std::string& newShape) {shape = newShape;}

void EntityProperties::setColor(const std::string& newColor) {color = newColor;}

void EntityProperties::setName(const std::string& newName) {name = newName;}

void EntityProperties::setBackground(const std::string& newBackground) {background = newBackground;}


std::string EntityProperties::getShape() const {return shape;}

std::string EntityProperties::getColor() const {return color;}

std::string EntityProperties::getName() const {return name;}

std::string EntityProperties::getBackground() const {return background;}
