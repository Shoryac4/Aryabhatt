#ifndef GRAHABASE_HPP
#define GRAHABASE_HPP

#include <string>
#include <vector>
#include "Constants.hpp"

namespace Aryabhatt {

    struct StateVector {
        double x, y, z;
        double vx, vy, vz;
    };

    struct PhysicalDNA {
        double GM;
        double radius;
        double j2;
        double albedo;
        double mass_ratio;
    };

    struct SiddhanticDNA {
        std::string tattva;
        std::string guna;
        std::vector<int> drishti; 
    };

    class Graha {
    public:
        std::string name;
        PhysicalDNA physics;
        SiddhanticDNA metaphysics;
        StateVector currentPos;
        
        // These were missing!
        double longitude;
        double distance;

        virtual void calculatePosition(double t) = 0;
        virtual ~Graha() {}
    };
}
#endif

