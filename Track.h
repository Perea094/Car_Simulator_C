#ifndef TRACK_H
#define TRACK_H

#include <string>


class Track
{
    private:
        std::string name; // Nombre de la pista
        std::string trackColor; // Color del suelo
        std::string trackBackground; // Fondo del suelo
        std::string trackShape; // Forma del suelo
        std::string wallsColor; // Color de los muros
        std::string wallsBackground; // Fondo de los murps
        std::string wallsShape;
        std::string finalTrackShape;
        std::string finalWallShape;

        int lanes; // Cantidad de carriles
        int length; // Longitud de carretera

    public:
        // Constructores
        Track();
        Track(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, 
              const std::string&, const std::string&, int, int);

        // Method
        std::string getFinalTrackShape() const;
        std::string getFinalWallsShape() const;

        // Setters 
        void setName(const std::string&);
        void setTrackColor(const std::string&);
        void setTrackBackground(const std::string&);
        void setTrackShape(const std::string&);
        void setWallsColor(const std::string&);
        void setWallsBackground(const std::string&);
        void setWallsShape(const std::string&);


        void setLanes(int);
        void setLength(int);


        // Getters
        std::string getName() const;
        std::string getTrackColor() const;
        std::string getTrackBackground() const;
        std::string getTrackShape() const;
        std::string getWallsColor() const;
        std::string getWallsBackground() const;
        std::string getWallsShape() const;

        int getLanes() const;
        int getLength() const;
};


#endif 