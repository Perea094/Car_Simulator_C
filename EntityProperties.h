#ifndef ENTITYPROPERTIES_H  // Guard para evitar múltiples inclusiones
#define ENTITYPROPERTIES_H

#include <string>

// Declaración de una clase
class EntityProperties {
    private:
        float CoordXY[2];
        float Width;
        float Length;
        float Speed;
        std::string Color; 
    public:
        void set_EntityWidth(float);
        void set_EntityLength(float);
        void set_EntitySpeed(float);
        void set_EntityColor(std::string);

        float get_EntityWidth();
        float get_EntityLength();
        float get_EntitySpeed();
        std::string get_EntityColor();

        void update_position(float, float);
        float retrieve_positionX();
        float retrieve_positionY();
};

#endif