#include "EntityProperties.h"

void EntityProperties::set_EntityWidth(float width){Width = width;};
void EntityProperties::set_EntityLength(float length){Length = length;};
void EntityProperties::set_EntitySpeed(float speed){Speed = speed;};
void EntityProperties::set_EntityColor(std::string color) {Color = color;};

float EntityProperties::get_EntityWidth(){return Width;};
float EntityProperties::get_EntityLength(){return Length;};
float EntityProperties::get_EntitySpeed(){return Speed;};
std::string EntityProperties::get_EntityColor(){return Color;};

void EntityProperties::update_position(float X,float Y)
{
    CoordXY[0] = X;
    CoordXY[1] = Y;
};
float EntityProperties::retrieve_positionX(){return CoordXY[0];};
float EntityProperties::retrieve_positionY(){return CoordXY[1];}
