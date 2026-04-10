#ifndef SURYA_HPP
#define SURYA_HPP

#include "../GrahaBase.hpp"
#include "../Sages/BrahmaguptaMath.hpp"
#include "../Sages/Nutation.hpp"
#include "../Sages/VectorPhysics.hpp"

namespace Aryabhatt {

    class Surya : public Graha {
    public:
        Surya() {
            name = "Surya";
            physics = { 1.32712440018e20, 695700, 7.25, 1.0, 0.00000021 }; 
            metaphysics = { "Agni", "Sattva", {7} };
        }
        Vector3D earthVector;

        void calculatePosition(double tau) override {
            double T = tau * 10.0; // Julian Centuries

            // --- L0 TERMS: Earth Heliocentric Longitude (Base + Perturbations) ---
            // Expanded to 35 terms to capture Venus, Mars, and Jupiter gravitational resonances
            static const std::vector<double> L0_A = {
                1.753470314, 0.033416563, 0.000348943, 0.000034970, 0.000034180, 0.000031360, 0.000026760, 
                0.000023430, 0.000013240, 0.000012730, 0.000011990, 0.000009900, 0.000009020, 0.000008570, 
                0.000007800, 0.000007530, 0.000007360, 0.000006870, 0.000006270, 0.000005290, 0.000005230, 
                0.000004810, 0.000004770, 0.000004710, 0.000004670, 0.000004520, 0.000004280, 0.000003630, 
                0.000003570, 0.000003500, 0.000003430, 0.000003080, 0.000002140, 0.000002060, 0.000001980
            };
            static const std::vector<double> L0_B = {
                0.0, 4.6692568, 4.62610, 2.74410, 2.82890, 3.62800, 4.41800, 
                6.13500, 0.74200, 2.03700, 1.10900, 5.23300, 2.04500, 3.50800, 
                1.17900, 2.53300, 4.58300, 4.20500, 2.92000, 5.88400, 2.69500, 
                1.51600, 3.25000, 6.08200, 5.14800, 1.83100, 5.13200, 2.00000, 
                1.29900, 1.75800, 5.67000, 2.89800, 0.31500, 3.84400, 1.81500
            };
            static const std::vector<double> L0_C = {
                0.0, 6283.07585, 12566.1517, 5753.3849, 3.52310, 77713.7715, 7860.4194, 
                3930.2097, 11506.7700, 529.6910, 15773.4350, 5884.9270, 26.2980, 398.1490, 
                5223.6940, 5507.5530, 18849.2280, 775.5230, 0.0670, 11790.6290, 7962.9800, 
                10977.0790, 5486.7780, 3193.1930, 5428.1630, 1179.0630, 25443.9360, 2192.0000, 
                8192.0000, 532.0000, 6283.0000, 32964.0000, 10977.0000, 5486.0000, 25443.0000
            };

            // --- L1 TERMS: Mean Motion & First-Order Perturbations ---
            static const std::vector<double> L1_A = {
                6283.075849991, 0.000136893, 0.000024473, 0.000005813, 0.000001815,
                0.000001557, 0.000001254, 0.000001150, 0.000001093, 0.000001053
            };
            static const std::vector<double> L1_B = {
                0.0, 4.6052, 1.9290, 0.4730, 1.7650, 2.5020, 5.1610, 1.1680, 2.8020, 5.2500
            };
            static const std::vector<double> L1_C = {
                0.0, 6283.07585, 12566.1517, 32964.467, 529.691, 59804.810, 26.298, 5753.385, 3.523, 11506.770
            };

            // --- L2 TERMS: Secular Acceleration ---
            static const std::vector<double> L2_A = {
                0.000033621, 0.000003050, 0.000000392, 0.000000318, 0.000000251
            };
            static const std::vector<double> L2_B = {
                3.1556, 1.4040, 2.3020, 3.0110, 5.5600
            };
            static const std::vector<double> L2_C = {
                0.0, 6283.07585, 12566.1517, 0.0, 529.691
            };

            // Calculate the summation series
            double val_L0 = BrahmaguptaMath::calculateVSOP(tau, L0_A, L0_B, L0_C);
            double val_L1 = BrahmaguptaMath::calculateVSOP(tau, L1_A, L1_B, L1_C);
            double val_L2 = BrahmaguptaMath::calculateVSOP(tau, L2_A, L2_B, L2_C);

            // True Heliocentric Longitude of Earth
            double L = val_L0 + (val_L1 * tau) + (val_L2 * tau * tau);
            
            // Earth Radius Vector (Distance in AU) - Expanded slightly
            static const std::vector<double> R0_A = {1.0001398, 0.0167070, 0.0001395, 0.0000308, 0.0000163, 0.0000160, 0.0000140};
            static const std::vector<double> R0_B = {0.0, 3.0984635, 3.05525, 5.1985, 1.1740, 2.5330, 4.5830};
            static const std::vector<double> R0_C = {0.0, 6283.07585, 12566.1517, 77713.7715, 7860.419, 3930.210, 11506.77};
            double R = BrahmaguptaMath::calculateVSOP(tau, R0_A, R0_B, R0_C);

              // Capture Earth's Heliocentric Vector (Latitude B is 0 for Earth)
            earthVector = VectorPhysics::toCartesian(L, 0.0, R);

            // 1. Geocentric Conversion (Sun from Earth's Perspective)
            double sunGeocentricLong = L + PI;
            sunGeocentricLong = BrahmaguptaMath::normalize(sunGeocentricLong);
            double sunLongDeg = sunGeocentricLong * RAD2DEG;

            // 2. Nutation Correction (True Equinox of Date)
            double deltaPsi = Nutation::getNutationInLongitude(T);
            
            // 3. Aberration Correction (Light travel time delay)
            double aberration = (-20.49552 / R) / 3600.0; 

            // Final Apparent Sayana Longitude
            longitude = sunLongDeg + deltaPsi + aberration;
            
            // Boundary enforcement
            longitude = std::fmod(longitude, 360.0);
            if (longitude < 0) longitude += 360.0;

            distance = R;
        }
    };
}
#endif

