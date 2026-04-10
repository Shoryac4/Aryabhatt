#ifndef CHANDRA_HPP
#define CHANDRA_HPP

#include "../GrahaBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Chandra : public Graha {
    public:
        Chandra() {
            name = "Chandra";
            physics = { 4.902e12, 1737, 5.14, 0.0123, 0.0 };
            metaphysics = { "Jala", "Sattva", {2} };
        }

        void calculatePosition(double tau) override {
            double T = tau * 10.0; // Julian Centuries from 2000

            // 1. Fundamental Arguments (Meeus/ELP-2000)
            // Mean Longitude of Moon (L')
            double Lp = 218.3164477 + 481267.8812307*T - 0.0015786*T*T;
            
            // Mean Elongation of Moon (D)
            double D = 297.8501921 + 445267.1114034*T - 0.0018819*T*T;
            
            // Mean Anomaly of Sun (M)
            double M = 357.5291092 + 35999.0502909*T - 0.0001536*T*T;
            
            // Mean Anomaly of Moon (M')
            double Mp = 134.9633964 + 477198.8675055*T + 0.0087414*T*T;
            
            // Moon's Argument of Latitude (F)
            double F = 93.2720950 + 483202.0175233*T - 0.0036539*T*T;

            // Convert all to Radians for Math
            double Dr = D * DEG2RAD;
            double Mr = M * DEG2RAD;
            double Mpr = Mp * DEG2RAD;
            double Fr = F * DEG2RAD;

            // 2. The Great Periodic Terms (The "True" Corrections)
            // Main Correction: Evection + Variation + Annual Equation
            double sigmaL = 6.288774 * std::sin(Mpr)                     // Principal Correction
                          + 1.274027 * std::sin(2*Dr - Mpr)              // Evection
                          + 0.658309 * std::sin(2*Dr)                    // Variation
                          + 0.213618 * std::sin(2*Mpr)                   // Second Principal
                          - 0.185116 * std::sin(Mr)                      // Annual Equation
                          - 0.114332 * std::sin(2*Fr)                    // Latitude Term
                          + 0.058793 * std::sin(2*Dr - 2*Mpr)
                          + 0.057066 * std::sin(2*Dr - Mr - Mpr)
                          + 0.053322 * std::sin(2*Dr + Mpr);

            // 3. Final Sayana Longitude
            longitude = Lp + sigmaL;
            longitude = std::fmod(longitude, 360.0);
            if (longitude < 0) longitude += 360.0;

            // Simple distance (Mean) for now
            distance = 384400.0 / 149597870.7; // AU
        }
    };
}
#endif

