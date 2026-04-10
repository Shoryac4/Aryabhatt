#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace Aryabhatt {
    // --- TIME & EPOCH ---
    const double J2000 = 2451545.0;            // Julian Date for Jan 1, 2000, 12:00 TT
    const double JULIAN_CENTURY = 36525.0;     // Days in a Julian Century
    const double JULIAN_MILLENNIUM = 365250.0; // Days in a Julian Millennium (for VSOP87)

    // --- PHYSICAL CONSTANTS (IAU 2012/2015) ---
    const double G = 6.67430e-11;              // Gravitational Constant (m^3 kg^-1 s^-2)
    const double AU = 149597870700.0;          // 1 Astronomical Unit in meters (Exact)
    const double SPEED_OF_LIGHT = 299792458.0; // m/s (Exact)
    
    // --- MATHEMATICAL PRECISION ---
    const double PI = 3.14159265358979323846;
    const double DEG2RAD = PI / 180.0;
    const double RAD2DEG = 180.0 / PI;
    const double AS2RAD = PI / (180.0 * 3600.0); // Arcseconds to Radians

    // --- ECLIPTIC CONSTANTS ---
    // Obliquity of the Ecliptic at J2000 (IAU 2006 model)
    const double EPSILON_0 = 23.4392794 * DEG2RAD; 
}

#endif

