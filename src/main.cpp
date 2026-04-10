#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include "Sages/Horizon.hpp"
#include "Sages/AryabhataCore.hpp"
#include "Sages/Nutation.hpp"
#include "Grahas/Surya.hpp"
#include "Grahas/Chandra.hpp"
#include "Grahas/Mangal.hpp"
#include "Grahas/Budh.hpp"
#include "Grahas/Shukra.hpp"
#include "Grahas/Guru.hpp"
#include "Grahas/Shani.hpp"
#include "Grahas/Aruna.hpp"
#include "Grahas/Varuna.hpp"
#include "Grahas/Yama.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace Aryabhatt;

    // Quick Nakshatra chart
    const char* nakshatras[] = {
        "Ashwini", "Bharani", "Kritika", "Rohini", "Mrigashira", "Ardra",
     "Punarvasu", "Pushya", "Ashlesha", "Magha", "Purva Phalguni",
     "Uttara Phalguni", "Hasta",
     "Chitra", "Swati", "Vishakha", "Anuradha", "Jyeshtha", "Mula",
      "Purva Ashadha", "Uttara Ashadha",
      "Shravana", "Dhanishta", "Shatabhisha", "Purva Bhadrapada",
      "Uttara Bhadrapada", "Revati"
    };

    //Rashi chart
    const char* rashis[] = {
        "Mesha", "Vrishabha", "Mithuna", "Karka", "Simha", "Kanya",
       "Tula", "Vrischika", "Dhanu", "Makara", "Kumbha", "Meena"
    };

    // 1. DMS Converter Helper
    std::string toDMS(double decimal_deg) {
    int d = static_cast<int>(decimal_deg);
    double m_full = std::abs(decimal_deg - d) * 60.0;
    int m = static_cast<int>(m_full);
    double s = (m_full - m) * 60.0;

    std::ostringstream oss;
    oss << d << "° " << m << "' " << std::fixed << std::setprecision(2) << s << "\"";
    return oss.str();
}

struct VedicPosition {
    std::string rashiName;
    int rashiIdx;
    std::string nakName;
    int nakIdx;
    int pada;
};


VedicPosition getAccurateMapping(double nirayana) {
    // Standardize to 0-360 range
    double cleanNirayana = std::fmod(nirayana, 360.0);
    if (cleanNirayana < 0) cleanNirayana += 360.0;

    // Convert to total arcminutes to avoid decimal rounding errors
    // 1 Degree = 60 Minutes. 1 Nakshatra = 800 Minutes.
    double totalMinutes = (cleanNirayana * 60.0) + 1e-9; // 1e-9 is a tiny epsilon safety
    
    int rashiIdx = static_cast<int>(totalMinutes / 1800.0); // 30 deg * 60
    int nakIdx   = static_cast<int>(totalMinutes / 800.0);  // 13.333 deg * 60
    int pada     = (static_cast<int>(totalMinutes) % 800) / 200 + 1;

    if (rashiIdx > 11) rashiIdx = 11;
    if (nakIdx > 26) nakIdx = 26;

    return {rashis[rashiIdx], rashiIdx, nakshatras[nakIdx], nakIdx, pada};
}

     struct EngineTime {
    int year, month, day, hour, minute, second;
    double utcDecimalHour;
};

EngineTime getEngineTime(bool useLiveTime, double tzOffset, int y = 0, int m = 0, int d = 0, double decimalHour = 0.0) {
    EngineTime et;

    if (useLiveTime) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* localTm = std::gmtime(&currentTime); // Pure UTC from system

        et.year = localTm->tm_year + 1900;
        et.month = localTm->tm_mon + 1;
        et.day = localTm->tm_mday;
        et.utcDecimalHour = localTm->tm_hour + (localTm->tm_min / 60.0) + (localTm->tm_sec / 3600.0);
    } else {
        et.year = y; et.month = m; et.day = d;
        double utcDecimal = decimalHour - tzOffset;

        // Correct for day rollover (e.g., 2:00 AM IST is 8:30 PM previous day UTC)
        if (utcDecimal < 0) { utcDecimal += 24.0; et.day -= 1; }
        else if (utcDecimal >= 24.0) { utcDecimal -= 24.0; et.day += 1; }

        et.utcDecimalHour = utcDecimal;
    }
    return et;
}

     void displayPlanetData(std::string name, double sayana, double ayan, double distance) {
    // 1. Math: Calculate Nirayana
    double nirayana = std::fmod(sayana - ayan + 360.0, 360.0);
    
    // 2. Math: Get Vedic Mapping (Indices, Names, and Padas)
    VedicPosition pos = getAccurateMapping(nirayana);

    // 3. Output Display
    std::cout << "======================================" << std::endl;
    std::cout << name << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    
    // Sayana (DMS + Decimal)
    std::cout << "  Sayana (DMS)    : " << toDMS(sayana) << std::endl;
    std::cout << "  Sayana (Deg)    : " << std::fixed << std::setprecision(6) << sayana << "°" << std::endl;
    
    // Nirayana (DMS + Decimal)
    std::cout << "  Nirayana (DMS)  : " << toDMS(nirayana) << std::endl;
    std::cout << "  Nirayana (Deg)  : " << nirayana << "°" << std::endl;
    
    // Rashi & Nakshatra Details (Names + Indices)
    std::cout << "  Rashi           : " << pos.rashiName << " (Index: " << pos.rashiIdx << ")" << std::endl;
    std::cout << "  Nakshatra       : " << pos.nakName << " (Index: " << pos.nakIdx << ")" << std::endl;
    std::cout << "  Pada            : " << pos.pada << std::endl;

    // Physical Distance
    std::cout << "  Distance        : " << distance << " AU" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    }

    //Upgrahas helper
    void displayPointData(std::string name, double nirayana, double ayan) {
    // 1. Calculate Sayana from Nirayana (The inverse of the planet logic)
    double sayana = std::fmod(nirayana + ayan + 360.0, 360.0);

    // 2. Get the High-Precision Vedic Mapping
    VedicPosition pos = getAccurateMapping(nirayana);

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "  " << name << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "  Sayana (Deg)    : " << std::fixed << std::setprecision(6) << sayana << "°" << std::endl;
    std::cout << "  Sayana (DMS)    : " << toDMS(sayana) << std::endl;
    std::cout << "  Nirayana (Deg)  : " << std::fixed << std::setprecision(6) << nirayana << "°" << std::endl;
    std::cout << "  Nirayana (DMS)  : " << toDMS(nirayana) << std::endl;
    std::cout << "  Rashi           : " << pos.rashiName << " (Index: " << pos.rashiIdx << ")" << std::endl;
    std::cout << "  Nakshatra       : " << pos.nakName << " (Index: " << pos.nakIdx << ")" << std::endl;
    std::cout << "  Pada            : " << pos.pada << std::endl;
    }


    //Header
    void printHeader(std::string mode) {
    std::cout << "======================================" << std::endl;
    std::cout << "  ARYABHATT ENGINE: " << mode << std::endl;
    std::cout << "======================================" << std::endl;
    }

    //Lagna display calculation
    void displayLagna(ObserverLocation obs, double jd_ut, double ayan) {
    // 1. Greenwich Mean Sidereal Time (GMST)
    double T = (jd_ut - 2451545.0) / 36525.0;
    double gmst = 280.46061837 + 360.98564736629 * (jd_ut - 2451545.0) + 0.000387933 * T * T;
    gmst = std::fmod(gmst, 360.0);
    if (gmst < 0) gmst += 360.0;

    // 2. Local Sidereal Time (LST)
    double lst = std::fmod(gmst + obs.longitude, 360.0);

    // 3. Trigonometry setup
    double lst_rad = lst * 3.14159265358979323846 / 180.0;
    double lat_rad = obs.latitude * 3.14159265358979323846 / 180.0;
    double eps_rad = 23.4392911 * 3.14159265358979323846 / 180.0;

    // 4. Calculate Ascendant (Sayana)
    double asc_rad = std::atan2(std::sin(lst_rad),
 std::cos(lst_rad) * std::cos(eps_rad) - std::sin(eps_rad) * std::tan(lat_rad));

    double asc_deg = asc_rad * 180.0 / 3.14159265358979323846;
    if (asc_deg < 0) asc_deg += 360.0;

    // 5. Convert to Nirayana
    double nirayanaLagna = std::fmod(asc_deg - ayan + 360.0, 360.0);

    // 6. Display Output
    std::cout << "======================================" << std::endl;
    std::cout << "  GEOGRAPHIC OBSERVER DATA" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "  Latitude        : " << obs.latitude << " deg N" << std::endl;
    std::cout << "  Longitude       : " << obs.longitude << " deg E" << std::endl;
    std::cout << "  Timezone Offset : GMT +" << obs.tzOffset << std::endl;

    displayPointData("LAGNA (Ascendant)", nirayanaLagna, ayan);
}

    //Main
    int main(int argc, char* argv[]) {
    // 1. Core Physics & Observer Initialization
    AryabhataCore engine;
    Surya sun; Chandra moon; Mangal mars; Budh mercury; Shukra venus;
    Guru jupiter; Shani saturn; Aruna uranus; Varuna neptune; Yama pluto;

    ObserverLocation localObserver; // Defaults to Vikasnagar (30.34, 77.75)
    EngineTime et;

        // 2. Unified Logic for Time Input
    if (argc >= 5) {
        // App Input Mode: uses Year, Month, Day, and Decimal Hour
        et = getEngineTime(false, 
                           localObserver.tzOffset, 
                           std::stoi(argv[1]), 
                           std::stoi(argv[2]), 
                           std::stoi(argv[3]), 
                           std::stod(argv[4]));
    } else {
        // Live Mode
        et = getEngineTime(true, localObserver.tzOffset);
    }


    // 3. Precise Core Calculations
    double jd_ut = engine.getJulianDay(et.year, et.month, et.day, et.utcDecimalHour);
    double tau = engine.getTau(jd_ut);
    double T = (jd_ut - 2451545.0) / 36525.0;
    double ayan = engine.getLahiriAyanamsha(jd_ut);

        // --------------------------------------------------------
    // 4. NEW HORIZON LOGIC CALL
    // --------------------------------------------------------
    // 4.1. Get JD for Midnight (00:00 UT) as the search baseline
    double jd_midnight = engine.getJulianDay(et.year, et.month, et.day, 0.0);

    // 4.2. Calculate Weekday (0=Sun, 1=Mon, ..., 6=Sat)
    int weekday = static_cast<int>(jd_midnight + 1.5) % 7;

    // 4.3. Calculate precise Rise/Set events for Vikasnagar
    RiseSet sunEvents = calculateSunEvents(jd_midnight, localObserver, engine);

    //4.4. sunrise and sunset time display
    displayHorizonEvents(sunEvents, localObserver);

    // 4.5. Calculate Mandi & Gulika based on the dynamic weekday
    calculateKalaVelas(jd_midnight, sunEvents.riseStart, sunEvents.setStart, weekday, localObserver, engine, ayan);
    // --------------------------------------------------------

    // 5. Print Engine Header
        std::cout << "======================================" << std::endl;
    std::cout << "  ARYABHATT ENGINE: " << (argc >= 5 ? "MANUAL SPEC" : "LIVE TRACKING") << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "  Target Date   : " << et.year << "-" << et.month << "-" << et.day << std::endl;
    std::cout << "  Target Time   : " << std::fixed << std::setprecision(4) << et.utcDecimalHour << " UT" << std::endl;
    std::cout << "  Julian Day    : " << std::fixed << std::setprecision(6) << jd_ut << std::endl;

    // Physics Processing
    sun.calculatePosition(tau);
    moon.calculatePosition(tau);
    mars.calculatePosition(tau, sun.earthVector);
    venus.calculatePosition(tau, sun.earthVector);
    mercury.calculatePosition(tau, sun.earthVector);
    jupiter.calculatePosition(tau, sun.earthVector);
    saturn.calculatePosition(tau, sun.earthVector);
    uranus.calculatePosition(tau, sun.earthVector);
    neptune.calculatePosition(tau, sun.earthVector);
    pluto.calculatePosition(tau, sun.earthVector);

    // 2. Display Calls
    displayPlanetData("SURYA (Sun)", sun.longitude, ayan, sun.distance);
    displayPlanetData("CHANDRA (Moon)", moon.longitude, ayan, moon.distance);
    displayPlanetData("BUDH (Mercury)", mercury.longitude, ayan, mercury.distance);
    displayPlanetData("SHUKRA (Venus)", venus.longitude, ayan, venus.distance);
    displayPlanetData("MANGAL (Mars)", mars.longitude, ayan, mars.distance);
    displayPlanetData("GURU (Jupiter)", jupiter.longitude, ayan, jupiter.distance);
    displayPlanetData("SHANI (Saturn)", saturn.longitude, ayan, saturn.distance);
    displayPlanetData("ARUNA (Uranus)", uranus.longitude, ayan, uranus.distance);
    displayPlanetData("VARUNA (Neptune)", neptune.longitude, ayan, neptune.distance);
    displayPlanetData("YAMA (Pluto)", pluto.longitude, ayan, pluto.distance);

    // ========================================================
    // CHHAYA GRAHAS (Lunar Nodes - Rahu & Ketu)
    // ========================================================
    std::cout << "======================================" << std::endl;
    std::cout << "  CHHAYA GRAHAS & UPGRAHAS" << std::endl;
    std::cout << "======================================" << std::endl;

     // Centuries from J2000
    // Meeus High-Precision Mean Node Algorithm
    double sayanaRahu = 125.04452 - 1934.136261 * T + 0.0020708 * T * T + (T * T * T / 450000.0);
    sayanaRahu = std::fmod(sayanaRahu, 360.0);
    if (sayanaRahu < 0) sayanaRahu += 360.0;

    double nirayanaRahu = std::fmod(sayanaRahu - ayan + 360.0, 360.0);
    double nirayanaKetu = std::fmod(nirayanaRahu + 180.0, 360.0);

    displayPointData("RAHU (North node)", nirayanaRahu, ayan);
    displayPointData("KETU (South node)", nirayanaKetu, ayan);

    // ========================================================
    // APRAKASHA GRAHAS (Sun-Based Upgrahas)
    // ========================================================
    double sunNirayana = std::fmod(sun.longitude - ayan + 360.0, 360.0);
    
    // Convert minutes to decimal (e.g., 133 deg 20 min = 133.333333)
    double dhooma = std::fmod(sunNirayana + 133.333333, 360.0);
    double vyatipata = std::fmod(360.0 - dhooma, 360.0);
    double parivesha = std::fmod(vyatipata + 180.0, 360.0);
    double indrachapa = std::fmod(360.0 - parivesha, 360.0);
    double upaketu = std::fmod(indrachapa + 16.666666, 360.0);

    // 4. Display Upgrahas
    displayPointData("DHOOMA", dhooma, ayan);
    displayPointData("VYATIPATA", vyatipata, ayan);
    displayPointData("PARIVESHA", parivesha, ayan);
    displayPointData("INDRACHAPA", indrachapa, ayan);
    displayPointData("UPAKETU (Sikhi)", upaketu, ayan);

        // Calculate and display Ascendant for the local observer
    displayLagna(localObserver, jd_ut, ayan);

return 0;
}

