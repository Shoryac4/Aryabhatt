#ifndef MANGAL_HPP
#define MANGAL_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Mangal : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Mars (Truncated for memory efficiency)
            
            // Mars Heliocentric Longitude (L0)
            static const std::vector<double> L0_A = { 1.259929, 0.126449, 0.003923, 0.000185, 0.000109, 0.000074, 0.000030 };
            static const std::vector<double> L0_B = { 0.0, 5.75330, 5.25300, 2.50200, 3.82000, 0.63000, 1.48000 };
            static const std::vector<double> L0_C = { 0.0, 3340.61243, 6681.22486, 10021.8370, 2192.0000, 77713.771, 3340.610 };
            
            // Mars Heliocentric Latitude (B0) - The Orbital Tilt
            static const std::vector<double> B0_A = { 0.032227, 0.003180, 0.000067, 0.000011 };
            static const std::vector<double> B0_B = { 0.44310, 0.00750, 5.86700, 2.76000 };
            static const std::vector<double> B0_C = { 3340.61243, 6681.22486, 10021.837, 2192.000 };

            // Mars Heliocentric Radius/Distance (R0)
            static const std::vector<double> R0_A = { 1.523636, 0.141566, 0.006622, 0.000424, 0.000032 };
            static const std::vector<double> R0_B = { 0.0, 4.18240, 3.68200, 3.18100, 2.68000 };
            static const std::vector<double> R0_C = { 0.0, 3340.61243, 6681.22486, 10021.837, 13362.450 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            // Return the 3D coordinate in space
            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Mangal() {
            name = "Mangal";
            physics = { 6.4171e23, 3389.5, 24.62, 1.524, 0.0934 }; 
            metaphysics = { "Agni", "Tamas", {3, 6} }; // Aries & Scorpio lord
        }
    };
}
#endif

