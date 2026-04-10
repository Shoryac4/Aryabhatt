#ifndef PLANET_BASE_HPP
#define PLANET_BASE_HPP

#include "../GrahaBase.hpp"
#include "../Sages/VectorPhysics.hpp"
#include "../Sages/Nutation.hpp"

namespace Aryabhatt {
    
    class PlanetBase : public Graha {
    protected:
        // Each specific planet (Mars, Jupiter, etc.) will define its own VSOP math here
        virtual Vector3D getHeliocentricVector(double tau) = 0;
        
    public:
          // Satisfy the pure virtual contract from GrahaBase
        void calculatePosition(double tau) override {
         // Default to Sun-centered if no Earth vector is provided
            calculatePosition(tau, {0, 0, 0}); 
        }
         // Overloading the calculatePosition to require Earth's position
        void calculatePosition(double tau, Vector3D earthPosHeliocentric) {
            double distance_au = 0.0;
            double tau_light = tau; // Start at target time
            Vector3D planetPos;

            // 1. The Iterative Light-Time Loop (Standard 3 iterations for MAS accuracy)
            for (int i = 0; i < 3; i++) {
                // Find where the planet was at 'tau_light'
                planetPos = getHeliocentricVector(tau_light);
                
                // Shift to Earth's perspective
                Vector3D geoPos = VectorPhysics::getGeocentricVector(planetPos, earthPosHeliocentric);
                distance_au = VectorPhysics::getDistance(geoPos);
                
                // Light travel time in Julian Millennia
                // 0.0057755183 days per AU / 365250 days per millennia
                double light_travel_tau = (distance_au * 0.0057755183) / 365250.0; 
                
                // Rewind the clock by the exact time light took to reach Earth
                tau_light = tau - light_travel_tau;
            }

            // 2. Final Geocentric Vector extraction
            Vector3D finalGeoPos = VectorPhysics::getGeocentricVector(planetPos, earthPosHeliocentric);
            
            // 3. Convert back to Spherical Degrees
            double raw_longitude = VectorPhysics::getLongitude(finalGeoPos);
            
            // 4. Apply Nutation and Aberration (Relativistic visual shift)
            double T = tau * 10.0;
            double deltaPsi = Nutation::getNutationInLongitude(T);
            
            // Annual aberration roughly factored by Earth's speed and light time
            longitude = raw_longitude + deltaPsi;
            longitude = std::fmod(longitude, 360.0);
            if (longitude < 0) longitude += 360.0;
            
            distance = distance_au;
        }
    };
}
#endif

