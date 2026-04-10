#ifndef VECTOR_PHYSICS_HPP
#define VECTOR_PHYSICS_HPP

#include <cmath>

namespace Aryabhatt {
    struct Vector3D {
        double x, y, z;
    };

    class VectorPhysics {
    public:
        // Converts Spherical (Longitude, Latitude, Radius) to 3D Cartesian (X, Y, Z)
        static Vector3D toCartesian(double L_deg, double B_deg, double R_au) {
            double L_rad = L_deg * (M_PI / 180.0);
            double B_rad = B_deg * (M_PI / 180.0);
            
            return {
                R_au * std::cos(B_rad) * std::cos(L_rad),
                R_au * std::cos(B_rad) * std::sin(L_rad),
                R_au * std::sin(B_rad)
            };
        }

        // Subtracts Earth Vector from Planet Vector to get the Geocentric view
        static Vector3D getGeocentricVector(Vector3D planet, Vector3D earth) {
            return { 
                planet.x - earth.x, 
                planet.y - earth.y, 
                planet.z - earth.z 
            };
        }

        // Extracts Longitude from a 3D Geocentric Vector
        static double getLongitude(Vector3D v) {
            double lon = std::atan2(v.y, v.x) * (180.0 / M_PI);
            if (lon < 0) lon += 360.0;
            return std::fmod(lon, 360.0);
        }

        // Extracts 3D Distance (Radius)
        static double getDistance(Vector3D v) {
            return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        }
    };
}
#endif

