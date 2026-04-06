#ifndef GRAHABASE_HPP
#define GRAHABASE_HPP

#include <string>
#include <vector>

struct PhysicalTraits {
    double mass;             // kg
    double radius;           // km
    double axialTilt;        // degrees
    double rotationPeriod;   // hours (negative = retrograde)
    double orbitalVelocity;  // km/s
    std::string atmosphere;
};

struct SiddhanticTraits {
    std::string tattva;      // Agni, Jala, etc.
    std::string guna;        // Sattva, Rajas, Tamas
    std::vector<int> drishti; // Houses of influence
};

class Graha {
public:
    std::string name;
    PhysicalTraits physics;
    SiddhanticTraits metaphysics;
    
    // Position coordinates (Updated in real-time)
    double longitude; 
    double latitude;
    double distance; 
};

#endif

