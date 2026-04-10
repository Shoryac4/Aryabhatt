#ifndef HORIZON_HPP
#define HORIZON_HPP

#include "AryabhataCore.hpp"

namespace Aryabhatt {

struct RiseSet {
    double riseStart, riseEnd;
    double setStart, setEnd;
    double dayLength_hours;
};

// 1. Calculate Sunrise and Sunset
RiseSet calculateSunEvents(double jd_midnight, ObserverLocation obs, AryabhataCore& engine);

// 2. Calculate Mandi & Gulika
void calculateKalaVelas(double jd_midnight, double rise_ut, double set_ut, int weekday, ObserverLocation obs, AryabhataCore& engine, double ayan);

//sunrise and sunset events
void displayHorizonEvents(RiseSet rs, ObserverLocation obs);

} // End of namespace Aryabhatt

#endif

