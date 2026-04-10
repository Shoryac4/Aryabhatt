#ifndef VARUNA_HPP
#define VARUNA_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Varuna : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Neptune (L, B, R)
            static const std::vector<double> L0_A = { 5.311486, 0.009386, 0.000045 };
            static const std::vector<double> L0_B = { 0.0, 1.4589, 4.3168 };
            static const std::vector<double> L0_C = { 0.0, 38.133035, 76.26607 };
            
            static const std::vector<double> B0_A = { 0.030960, 0.000100 };
            static const std::vector<double> B0_B = { 0.3559, 4.6738 };
            static const std::vector<double> B0_C = { 38.133035, 76.26607 };

            static const std::vector<double> R0_A = { 30.068963, 0.282563, 0.001328 };
            static const std::vector<double> R0_B = { 0.0, 6.1705, 2.7475 };
            static const std::vector<double> R0_C = { 0.0, 38.133035, 76.26607 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Varuna() {
            name = "Varuna";
            physics = { 1.0241e26, 24622.0, 60182.0, 30.07, 0.0086 }; 
            metaphysics = { "Jala", "Sattva", {12} }; // Modern: Pisces co-lord
        }
    };
}
#endif
