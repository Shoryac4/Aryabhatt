#ifndef BRAHMAGUPTAMATH_HPP
#define BRAHMAGUPTAMATH_HPP

#include <cmath>

namespace Brahmagupta {
    const double PI = 3.14159265358979323846;
    const double RAD = PI / 180.0;

    // High-precision normalization of angles to 0-360 degrees
    inline double rev(double angle) {
        return angle - 360.0 * floor(angle / 360.0);
    }

    // VSOP87 Summation Logic (Analytical Arcsecond Calculation)
    inline double calculateSeries(double t, double A, double B, double C) {
        return A * cos(B + C * t);
    }
}

#endif

