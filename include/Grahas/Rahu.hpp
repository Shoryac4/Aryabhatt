#ifndef RAHU_HPP
#define RAHU_HPP

#include "../GrahaBase.hpp"

namespace Aryabhatt {
    class Rahu : public Graha {
    public:
        Rahu() { name = "Rahu"; }

        void calculatePosition(double tau) override {
            double T = tau * 10.0;
            
            // 1. Mean Node (The base line)
            double Omega = 125.0445479 - 1934.1362891 * T + 0.0020754 * T * T;
            
            // 2. Fundamental Arguments (Required for True Node)
            double D = (297.8501921 + 445267.1114034 * T) * (M_PI/180.0);
            double M = (357.5291092 + 35999.0502909 * T) * (M_PI/180.0);
            double Mp = (134.9633964 + 477198.8675055 * T) * (M_PI/180.0);
            double F = (93.2720950 + 483202.0175233 * T) * (M_PI/180.0);

            // 3. True Node Perturbations (The "Wobble")
            double correction = -1.4979 * std::sin(2*(D-F))
                               -0.1500 * std::sin(M)
                               -0.1226 * std::sin(2*D)
                               +0.1176 * std::sin(2*F)
                               -0.0801 * std::sin(2*(Mp-F));

            longitude = std::fmod(Omega + correction, 360.0);
            if (longitude < 0) longitude += 360.0;
        }
    };
}
#endif

