#include "Horizon.hpp"
#include "AryabhataCore.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Aryabhatt {

// Helper: Calculate Sun's altitude at a specific UT hour
double getSolarAltitude(double jd_ut, ObserverLocation obs, AryabhataCore& engine) {
    // 1. Get Sun's Tropical Longitude
    double tCenturies = (jd_ut - 2451545.0) / 36525.0;
    double L0 = 280.46646 + 36000.76983 * tCenturies + 0.0003032 * tCenturies * tCenturies;
    double sunLong_deg = std::fmod(L0, 360.0);
    if (sunLong_deg < 0) sunLong_deg += 360.0;
    
    double sunLong_rad = sunLong_deg * M_PI / 180.0;

    // 2. Ecliptic Obliquity (Using the tCenturies we already calculated)
    double eps_deg = 23.4392911 - 0.0130042 * tCenturies;
    double eps_rad = eps_deg * M_PI / 180.0;

    // 3. Right Ascension (RA) and Declination (Dec)
    double dec_rad = std::asin(std::sin(eps_rad) * std::sin(sunLong_rad));
    double ra_rad = std::atan2(std::cos(eps_rad) * std::sin(sunLong_rad), std::cos(sunLong_rad));
    double ra_deg = ra_rad * 180.0 / M_PI;
    if (ra_deg < 0) ra_deg += 360.0;

    // 4. Local Sidereal Time (LST)
    double gmst = 280.46061837 + 360.98564736629 * (jd_ut - 2451545.0) + 0.000387933 * std::pow(tCenturies, 2);
    double lst = std::fmod(gmst + obs.longitude, 360.0);
    if (lst < 0) lst += 360.0;

    // 5. Hour Angle (HA)
    double ha_deg = lst - ra_deg;
    double ha_rad = ha_deg * M_PI / 180.0;
    double lat_rad = obs.latitude * M_PI / 180.0;

    // 6. Altitude Calculation
    double alt_rad = std::asin(std::sin(lat_rad) * std::sin(dec_rad) +
                               std::cos(lat_rad) * std::cos(dec_rad) * std::cos(ha_rad));

    return alt_rad * 180.0 / M_PI;
}

// Helper: Binary Search for exact time
double findPreciseTime(double targetAlt, double jd_start, double hourStart, double hourEnd, ObserverLocation obs, AryabhataCore& engine, bool isRise) {
    double low = hourStart;
    double high = hourEnd;
    double mid, alt;

    for(int i = 0; i < 40; i++) {
        mid = (low + high) / 2.0;
        alt = getSolarAltitude(jd_start + (mid / 24.0), obs, engine);

        if (isRise) {
            if (alt < targetAlt) low = mid; else high = mid;
        } else {
            if (alt > targetAlt) low = mid; else high = mid;
        }
    }
    return mid;
}

    RiseSet calculateSunEvents(double jd_midnight, ObserverLocation obs, AryabhataCore& engine) {
    RiseSet rs;
    double elevation_m = 450.0; // Vikasnagar default

    double dip = 0.0293 * std::sqrt(elevation_m);
    double refraction = 0.5667;
    double semidiameter = 0.2666;

    double targetStart = -(refraction + semidiameter + dip);
    double targetEnd = -(refraction - semidiameter + dip);

    rs.riseStart = findPreciseTime(targetStart, jd_midnight, 0.0, 12.0, obs, engine, true);
    rs.riseEnd = findPreciseTime(targetEnd, jd_midnight, 0.0, 12.0, obs, engine, true);

    rs.setStart = findPreciseTime(targetStart, jd_midnight, 12.0, 24.0, obs, engine, false);
    rs.setEnd = findPreciseTime(targetEnd, jd_midnight, 12.0, 24.0, obs, engine, false);

    rs.dayLength_hours = rs.setEnd - rs.riseStart;
    return rs;
}

    void calculateKalaVelas(double jd_midnight, double rise_ut, double set_ut, int weekday, ObserverLocation obs, AryabhataCore& engine, double ayan) {
    double partLength = (set_ut - rise_ut) / 8.0;

    // Segment mapping (0=Sunday ... 6=Saturday)
    int gulikaSegments[] = {6, 5, 4, 3, 2, 1, 0};
    int segIdx = gulikaSegments[weekday];

    double gulikaTime_ut = rise_ut + (segIdx * partLength);
    double mandiTime_ut = rise_ut + (segIdx * partLength) + (partLength / 2.0);

    std::cout << "======================================" << std::endl;
    std::cout << "  KALA-VELAS (Mandi & Gulika)" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "  Mandi UT Time   : " << std::fixed << std::setprecision(4) << mandiTime_ut << " hrs" << std::endl;
    std::cout << "  Gulika UT Time  : " << std::fixed << std::setprecision(4) << gulikaTime_ut << " hrs" << std::endl;
}
    void displayHorizonEvents(RiseSet rs, ObserverLocation obs) {
    std::cout << "======================================" << std::endl;
    std::cout << "  HORIZON EVENTS (Local Time)" << std::endl;
    std::cout << "======================================" << std::endl;
    
    double localSunrise = rs.riseStart + obs.tzOffset;
    double localSunset = rs.setEnd + obs.tzOffset;

    if (localSunrise >= 24.0) localSunrise -= 24.0;
    if (localSunrise < 0.0) localSunrise += 24.0;
    if (localSunset >= 24.0) localSunset -= 24.0;
    if (localSunset < 0.0) localSunset += 24.0;

    std::cout << "  Sunrise         : " << std::fixed << std::setprecision(4) << localSunrise << " hrs" << std::endl;
    std::cout << "  Sunset          : " << std::fixed << std::setprecision(4) << localSunset << " hrs" << std::endl;
    std::cout << "  Day Length      : " << std::fixed << std::setprecision(4) << rs.dayLength_hours << " hrs" << std::endl;
}

} // End of namespace Aryabhatt

