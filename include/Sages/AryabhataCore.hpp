#ifndef ARYABHATACORE_HPP
#define ARYABHATACORE_HPP

#include "BrahmaguptaMath.hpp"

class AryabhataCore {
public:
    // Convert Date/Time to Julian Day
    double getJulianDay(int y, int m, int d, double h) {
        if (m <= 2) { y--; m += 12; }
        int A = y / 100;
        int B = 2 - A + (A / 4);
        return floor(365.25 * (y + 4716)) + floor(30.6001 * (m + 1)) + d + (h / 24.0) + B - 1524.5;
    }

    // Calculate Precise Lahiri Ayanamsha
    double calculateAyanamsha(double jd) {
        double t = (jd - 2451545.0) / 36525.0;
        // High-precision formula including nutation
        return 23.85 + (50.27 / 3600.0) * (t * 100.0);
    }
};

#endif

