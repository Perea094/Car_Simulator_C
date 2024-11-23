#ifndef ENTITYPROPERTIES_H  // Guard para evitar múltiples inclusiones
#define ENTITYPROPERTIES_H

#include <string> //Incluimos la libreria string

// Declaración de una clase
class EntityProperties {
    protected: // Parametros protegidos
        std::string shape;
        std::string color;
        std::string name;
        std::string background;
        std::string finalShape;

    public:
        // Constructores
        EntityProperties();
        EntityProperties(const std::string&, const std::string&, 
                         const std::string&, const std::string&);

        // Method
        std::string getFinalShape() const;
        // Setters
        void setShape(const std::string&);
        void setColor(const std::string&);
        void setName(const std::string&);
        void setBackground(const std::string&);

        // Getters
        std::string getShape() const;
        std::string getColor() const;
        std::string getName() const;
        std::string getBackground() const;

};

#endif