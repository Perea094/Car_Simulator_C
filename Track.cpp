#include "Track.h"

// Constructor por defecto
Track::Track()
    : name("Default Track"), trackColor("37"), trackBackground("40"), trackShape("-"),
      wallsColor("37"), wallsBackground("40"), wallsShape("="), lanes(5), length(30) {}

// Constructor parametrizado
Track::Track(const std::string& name, const std::string& trackColor, const std::string& trackBackground, const std::string& trackShape, 
             const std::string& wallsColor, const std::string& wallsBackground, const std::string& wallsShape, int lanes, int length)
    : name(name), trackColor(trackColor), trackBackground(trackBackground), trackShape(trackShape), 
      wallsColor(wallsColor), wallsBackground(wallsBackground), wallsShape(wallsShape), lanes(lanes), length(length) {}

//Method
std::string Track::getFinalTrackShape() const
{
    const std::string ansiPart1 = "\e[";
    std::string ansiCommand = ansiPart1 + trackBackground + ";" + trackColor + "m" + trackShape;
    return ansiCommand;
}

std::string Track::getFinalWallsShape() const
{
    const std::string ansiPart1 = "\e[";
    std::string ansiCommand = ansiPart1 + wallsBackground + ";" + wallsBackground + "m" + wallsShape;
    return ansiCommand;
}


// Setters
void Track::setName(const std::string& newName) {name = newName;}

void Track::setTrackColor(const std::string& newTrackColor) {trackColor = newTrackColor;}

void Track::setTrackBackground(const std::string& newTrackBackground) {trackBackground = newTrackBackground;}

void Track::setTrackShape(const std::string& newShape) {trackShape = newShape;}

void Track::setWallsColor(const std::string& newWallsColor) {wallsColor = newWallsColor;}

void Track::setWallsBackground(const std::string& newWallsBackground) {wallsBackground = newWallsBackground;}

void Track::setWallsShape(const std::string& newWallsShape) {wallsShape = newWallsShape;}

void Track::setLanes(int newLanes) 
{
    if (newLanes > 1) {lanes = newLanes;}
}

void Track::setLength(int newLength) 
{
    if (newLength > 10) {length = newLength;}
}

// Getters
std::string Track::getName() const {return name;}

std::string Track::getTrackColor() const {return trackColor;}

std::string Track::getTrackBackground() const {return trackBackground;}

std::string Track::getTrackShape() const {return trackShape;}

std::string Track::getWallsColor() const {return wallsColor;}

std::string Track::getWallsBackground() const {return wallsBackground;}

std::string Track::getWallsShape() const {return wallsShape;}

int Track::getLanes() const {return lanes;}

int Track::getLength() const {return length;}