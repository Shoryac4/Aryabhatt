#ifndef BUDH_HPP
#define BUDH_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Budh : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Mercury (L, B, R)
            static const std::vector<double> L0_A = { 4.402608, 0.190998, 0.014264, 0.001601, 0.000213 };
            static const std::vector<double> L0_B = { 0.0, 5.2523, 5.5684, 1.4851, 1.9443 };
            static const std::vector<double> L0_C = { 0.0, 26087.90314, 52175.80628, 78263.709, 104351.61 };
            
            static const std::vector<double> B0_A = { 0.122137, 0.012543, 0.001150, 0.000100 };
            static const std::vector<double> B0_B = { 4.9818, 4.4172, 4.7334, 0.6501 };
            static const std::vector<double> B0_C = { 26087.90314, 52175.80628, 78263.709, 104351.61 };

            static const std::vector<double> R0_A = { 0.387098, 0.079450, 0.008316, 0.000940, 0.000114 };
            static const std::vector<double> R0_B = { 0.0, 0.5398, 0.8559, 3.9634, 4.4226 };
            static const std::vector<double> R0_C = { 0.0, 26087.90314, 52175.80628, 78263.709, 104351.61 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Budh() {
            name = "Budh";
            physics = { 3.3011e23, 2439.7, 87.97, 0.387, 0.2056 }; 
            metaphysics = { "Prithvi", "Rajas", {3, 6} }; // Gemini & Virgo lord
        }
    };
}
#endif

