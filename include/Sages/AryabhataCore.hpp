#ifndef ARYABHATACORE_HPP
#define ARYABHATACORE_HPP

#include "BrahmaguptaMath.hpp"

namespace Aryabhatt {

    // observer location
    struct ObserverLocation {
    double latitude;
    double longitude;
    double tzOffset; 

    // Defaults to Vikasnagar
    ObserverLocation(double lat = 30.34, double lon = 77.75, double tz = 5.5)
        : latitude(lat), longitude(lon), tzOffset(tz) {}
};

    class AryabhataCore {
    public:
        // Updated to accept 4 arguments: Year, Month, Day, Hour
        static double getJulianDay(int y, int m, int d, double h) {
            if (m <= 2) { y--; m += 12; }
            int A = y / 100;
            int B = 2 - A + (A / 4);
            // Day + (Hour/24) combines the time into a single decimal day
            double day_decimal = d + (h / 24.0);
            return std::floor(365.25 * (y + 4716)) + 
                   std::floor(30.6001 * (m + 1)) + day_decimal + B - 1524.5;
        }

        static double calculateDeltaT(double year) {
            double t = year - 2000;
            return 62.92 + 0.32217 * t + 0.005589 * std::pow(t, 2);
        }

        static double getTau(double jd_ut) {
            double deltaT = calculateDeltaT(2000 + (jd_ut - J2000) / 365.25);
            double jd_td = jd_ut + (deltaT / 86400.0);
            return (jd_td - J2000) / JULIAN_MILLENNIUM;
        }

        static double getLahiriAyanamsha(double jd) {
    double T = (jd - 2451545.0) / 36525.0;
    // High-precision IAU 2006 Precession + Chitra Baseline
    // Value for 2026-04-06 should be approx 24.223 degrees
    return 23.85 + (5028.796195 * T + 1.11113 * T * T) / 3600.0;
}

    };
}
#endif

