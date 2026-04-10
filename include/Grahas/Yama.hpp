#ifndef YAMA_HPP
#define YAMA_HPP

#include "PlanetBase.hpp"

namespace Aryabhatt {

    class Yama : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            double T = tau * 10.0; // Centuries from J2000
            
            // Mean elements for Pluto (Meeus/JPL)
            double L = 238.92881 + 145.2078 * T;
            double a = 39.48168677;
            double e = 0.24880766;
            double i = 17.14175;
            double Node = 110.30347;
            double peri = 113.76329;

            // Simple Keplarian to Cartesian for Pluto's extreme orbit
            double M = (L - peri) * (M_PI/180.0);
            double E = M + e * std::sin(M); // One iteration for Eccentric Anomaly
            for(int j=0; j<3; j++) E = E - (E - e*std::sin(E) - M) / (1 - e*std::cos(E));

            double x_orb = a * (std::cos(E) - e);
            double y_orb = a * std::sqrt(1 - e*e) * std::sin(E);

            // Rotation to Ecliptic
            double cosN = std::cos(Node * M_PI/180.0);
            double sinN = std::sin(Node * M_PI/180.0);
            double cosi = std::cos(i * M_PI/180.0);
            double sini = std::sin(i * M_PI/180.0);
            double cosW = std::cos((peri-Node) * M_PI/180.0);
            double sinW = std::sin((peri-Node) * M_PI/180.0);

            Vector3D v;
            v.x = x_orb * (cosN*cosW - sinN*sinW*cosi) - y_orb * (cosN*sinW + sinN*cosW*cosi);
            v.y = x_orb * (sinN*cosW + cosN*sinW*cosi) - y_orb * (sinN*sinW - cosN*cosW*cosi);
            v.z = x_orb * (sinW*sini) + y_orb * (cosW*sini);

            return v;
        }

    public:
        Yama() {
            name = "Yama";
            physics = { 1.303e22, 1188.3, 90560.0, 39.48, 0.2488 }; 
            metaphysics = { "Prithvi", "Tamas", {8} }; // Modern: Scorpio co-lord
        }
    };
}
#endif

