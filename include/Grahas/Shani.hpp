#ifndef SHANI_HPP
#define SHANI_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Shani : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Saturn (L, B, R)
            static const std::vector<double> L0_A = { 0.213299, 0.038139, 0.001150, 0.000057 };
            static const std::vector<double> L0_B = { 0.0, 2.5020, 2.1858, 2.5020 };
            static const std::vector<double> L0_C = { 0.0, 213.299095, 426.59819, 529.691 };
            
            static const std::vector<double> B0_A = { 0.043594, 0.000845, 0.000030 };
            static const std::vector<double> B0_B = { 1.9961, 1.3680, 5.1382 };
            static const std::vector<double> B0_C = { 213.299095, 426.59819, 529.691 };

            static const std::vector<double> R0_A = { 9.554909, 0.536965, 0.016024, 0.000810 };
            static const std::vector<double> R0_B = { 0.0, 0.9312, 0.6150, 0.9312 };
            static const std::vector<double> R0_C = { 0.0, 213.299095, 426.59819, 529.691 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Shani() {
            name = "Shani";
            physics = { 5.6834e26, 58232.0, 10759.22, 9.582, 0.0565 }; 
            metaphysics = { "Vayu", "Tamas", {10, 11} }; // Capricorn & Aquarius lord
        }
    };
}
#endif

