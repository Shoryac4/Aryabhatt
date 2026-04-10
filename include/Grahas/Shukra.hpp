#ifndef SHUKRA_HPP
#define SHUKRA_HPP

#include "PlanetBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"

namespace Aryabhatt {

    class Shukra : public PlanetBase {
    protected:
        Vector3D getHeliocentricVector(double tau) override {
            // VSOP87 Top Terms for Venus (L, B, R)
            static const std::vector<double> L0_A = { 3.176146, 0.004616, 0.000030 };
            static const std::vector<double> L0_B = { 0.0, 5.3780, 5.0618 };
            static const std::vector<double> L0_C = { 0.0, 10213.28554, 20426.57109 };
            
            static const std::vector<double> B0_A = { 0.059288, 0.000287 };
            static const std::vector<double> B0_B = { 0.5385, 0.2223 };
            static const std::vector<double> B0_C = { 10213.28554, 20426.57109 };

            static const std::vector<double> R0_A = { 0.723329, 0.004926, 0.000033 };
            static const std::vector<double> R0_B = { 0.0, 3.8073, 3.4910 };
            static const std::vector<double> R0_C = { 0.0, 10213.28554, 20426.57109 };

            double L = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double B = BrahmaguptaMath::calculateVSOP(tau, B0_A, B0_B, B0_C);
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

            return VectorPhysics::toCartesian(L, B, R);
        }

    public:
        Shukra() {
            name = "Shukra";
            physics = { 4.8675e24, 6051.8, 224.70, 0.723, 0.0067 }; 
            metaphysics = { "Jala", "Rajas", {2, 7} }; // Taurus & Libra lord
        }
    };
}
#endif

