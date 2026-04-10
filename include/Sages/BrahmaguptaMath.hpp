#ifndef BRAHMAGUPTAMATH_HPP
#define BRAHMAGUPTAMATH_HPP

#include <cmath>
#include <vector>
#include "../Constants.hpp"

namespace Aryabhatt {

    class BrahmaguptaMath {
    public:
        // High-precision Angle Normalization (0 to 2*PI)
        static double normalize(double angle) {
            double res = std::fmod(angle, 2.0 * PI);
            if (res < 0) res += 2.0 * PI;
            return res;
        }

        // VSOP87 Summation Engine: Calculates a single variable (L, B, or R)
        // t = Julian millennia (tau)
        // A, B, C are the VSOP87 coefficients
        static double calculateVSOP(double t, const std::vector<double>& A, 
                                   const std::vector<double>& B, 
                                   const std::vector<double>& C) {
            double sum = 0.0;
            for (size_t i = 0; i < A.size(); ++i) {
                sum += A[i] * std::cos(B[i] + C[i] * t);
            }
            return sum;
        }

        // Polynomial evaluation (Horner's Method) for L0 + L1*t + L2*t^2...
        static double evaluatePolynomial(double t, const std::vector<double>& coeffs) {
            double result = 0.0;
            for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it) {
                result = result * t + (*it);
            }
            return result;
        }
    };
}

#endif

