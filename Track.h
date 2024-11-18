#ifndef TRACK_H
#define TRACK_H

#include <string>


class Track
{
    private:
        std::string TrackName;
        float TrackFriction;
        std::string TrackColor;
        float TrackLimits;
        int TrackLanes;
    public:
        void setTrackColor(std::string);
        void setTrackName(std::string);
        void setTrackFriction(float);
        void setTrackLimits(float);
        void setTrackLanes(int);

        
        std::string getTrackName();
        std::string getTrackColor();
        float getTrackFriction();
        float getTrackLimits();
        int getTrackLanes();
};


#endif 