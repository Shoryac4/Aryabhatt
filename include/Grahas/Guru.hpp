#ifndef GURU_HPP
#define GURU_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Guru : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Jupiter (L, B, R)
            static const std::vector<double> L0_A = { 0.529691, 0.033621, 0.000676, 0.000057 };
            static const std::vector<double> L0_B = { 0.0, 5.0355, 4.7193, 0.6361 };
            static const std::vector<double> L0_C = { 0.0, 529.690965, 1059.38193, 2192.000 };
            
            static const std::vector<double> B0_A = { 0.022839, 0.000652, 0.000030 };
            static const std::vector<double> B0_B = { 1.7610, 0.4968, 5.2162 };
            static const std::vector<double> B0_C = { 529.690965, 1059.38193, 2192.000 };

            static const std::vector<double> R0_A = { 5.202596, 0.252033, 0.005085, 0.000424 };
            static const std::vector<double> R0_B = { 0.0, 3.4646, 3.1484, 5.3482 };
            static const std::vector<double> R0_C = { 0.0, 529.690965, 1059.38193, 2192.000 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Guru() {
            name = "Guru";
            physics = { 1.8982e27, 69911.0, 4332.59, 5.204, 0.0489 }; 
            metaphysics = { "Akasha", "Sattva", {9, 12} }; // Sagittarius & Pisces lord
        }
    };
}
#endif

