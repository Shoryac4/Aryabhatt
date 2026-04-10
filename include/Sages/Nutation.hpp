#ifndef NUTATION_HPP
#define NUTATION_HPP

#include <cmath>
#include "../Constants.hpp"

namespace Aryabhatt {

    class Nutation {
    public:
        // Returns Nutation in Longitude (Delta Psi) in degrees
        static double getNutationInLongitude(double T) {
            // T is Julian Centuries from J2000.0
            
            // Mean elongation of the Moon from the Sun
            double D = (297.85036 + 445267.111480 * T) * DEG2RAD;
            // Mean anomaly of the Sun (Earth)
            double M = (357.52772 + 35999.050340 * T) * DEG2RAD;
            // Mean anomaly of the Moon
            double M_prime = (134.96298 + 477198.867398 * T) * DEG2RAD;
            // Argument of latitude of the Moon
            double F = (93.27191 + 483202.017538 * T) * DEG2RAD;
            // Longitude of the ascending node of the Moon
            double Omega = (125.04452 - 1934.136261 * T) * DEG2RAD;

            // IAU 1980 Nutation Series (Top 4 dominant terms in 0.0001 arcseconds)
            double deltaPsi_arcsec = 
                (-171996 * std::sin(Omega) - 174.2 * T * std::sin(Omega)) +
                (-13187 * std::sin(2 * M) - 1.6 * T * std::sin(2 * M)) +
                (-2274 * std::sin(2 * F) - 0.2 * T * std::sin(2 * F)) +
                (2062 * std::sin(2 * Omega) + 0.2 * T * std::sin(2 * Omega)) +
                (1426 * std::sin(M)) + 
                (712 * std::sin(M_prime));

            // Convert from 0.0001 arcseconds to degrees
            return (deltaPsi_arcsec / 10000.0) / 3600.0;
        }

        // True Obliquity of the Ecliptic
        static double getTrueObliquity(double T) {
            // Mean Obliquity (IAU 2006)
            double eps0 = 23.43927944444444 - (46.8150 / 3600.0) * T;
            
            double Omega = (125.04452 - 1934.136261 * T) * DEG2RAD;
            double M = (357.52772 + 35999.050340 * T) * DEG2RAD;

            // Nutation in Obliquity (Delta Epsilon)
            double deltaEps_arcsec = 
                (92025 * std::cos(Omega) + 8.9 * T * std::cos(Omega)) +
                (5736 * std::cos(2 * M) - 3.1 * T * std::cos(2 * M)) +
                (977 * std::cos(2 * Omega) - 0.5 * T * std::cos(2 * Omega));

            double deltaEps_deg = (deltaEps_arcsec / 10000.0) / 3600.0;
            return eps0 + deltaEps_deg;
        }
    };
}
#endif

