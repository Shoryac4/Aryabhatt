#include <iostream>
#include <iomanip>
#include "../include/Sages/AryabhataCore.hpp"
#include "../include/Grahas/Surya.hpp"

int main() {
    AryabhataCore engine;
    Surya sun;

    // Set calculation time: April 6, 2026, at 12:00 PM
    double jd = engine.getJulianDay(2026, 4, 6, 12.0);
    double ayan = engine.calculateAyanamsha(jd);

    std::cout << "======================================" << std::endl;
    std::cout << "     ARYABHATT ASTRONOMY ENGINE       " << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Julian Day: " << std::fixed << std::setprecision(2) << jd << std::endl;
    std::cout << "Ayanamsha:  " << std::setprecision(6) << ayan << " degrees" << std::endl;
    std::cout << "Object:     " << sun.name << std::endl;
    std::cout << "Mass:       " << sun.physics.mass << " kg" << std::endl;
    std::cout << "Tattva:     " << sun.metaphysics.tattva << std::endl;
    std::cout << "======================================" << std::endl;

    return 0;
}

