#ifndef ARUNA_HPP
#define ARUNA_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Aruna : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Uranus (L, B, R)
            static const std::vector<double> L0_A = { 5.481293, 0.046182, 0.000951, 0.000072 };
            static const std::vector<double> L0_B = { 0.0, 5.0937, 3.8641, 2.5020 };
            static const std::vector<double> L0_C = { 0.0, 74.781598, 149.56319, 529.691 };
            
            static const std::vector<double> B0_A = { 0.013504, 0.000030 };
            static const std::vector<double> B0_B = { 1.6706, 5.3482 };
            static const std::vector<double> B0_C = { 74.781598, 1059.3819 };

            static const std::vector<double> R0_A = { 19.191263, 0.884102, 0.020412, 0.001384 };
            static const std::vector<double> R0_B = { 0.0, 3.5228, 2.2932, 0.9312 };
            static const std::vector<double> R0_C = { 0.0, 74.781598, 149.56319, 213.299 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Aruna() {
            name = "Aruna";
            physics = { 8.6810e25, 25362.0, 30688.5, 19.218, 0.0472 }; 
            metaphysics = { "Akasha", "Sattva", {11} }; // Modern: Aquarius co-lord
        }
    };
}
#endif

