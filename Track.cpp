#include "Track.h"

void Track::setTrackColor(std::string color){TrackColor = color;}
void Track::setTrackName(std::string name){TrackName = name;}
void Track::setTrackFriction(float friction){TrackFriction = friction;}
void Track::setTrackLimits(float limits){TrackLimits = limits;}
void Track::setTrackLanes(int numLanes){TrackLanes = numLanes;}

std::string Track::getTrackColor(){return TrackColor;}
std::string Track::getTrackName(){return TrackName;}
float Track::getTrackFriction(){return TrackFriction;}
float Track::getTrackLimits(){return TrackLimits;}
int Track::getTrackLanes(){return TrackLanes;}