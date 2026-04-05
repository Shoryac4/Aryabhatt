#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Namespace for constants defined by Brahmagupta (e.g., zero, sine values)
namespace BrahmaguptaSeries {
    const double PI = 3.14159265358979323846;
    const double RAD = PI / 180.0;
}

// Data structure for the "Position of the Planet"
struct GrahaSthiti {
    double longitude;
    double latitude;
    double distance;
};

class AryabhataCore {
public:
    // Varahamihira specialized in the precision of the Zodiac and Ayanamsha
    double VarahamihiraAyanamsha(double jd) {
        double t = (jd - 2451545.0) / 36525.0; 
        // High precision Lahiri Ayanamsha (Chitra Paksha)
        return 23.85 + (50.27 / 3600.0) * (t * 100.0 + 50.0); 
    }

    // Bhaskara II pioneered concepts of instantaneous motion (calculus)
    // Used here for Manda Phala (Equation of Center)
    double BhaskaraMandaPhala(double meanAnomaly, double eccentricity) {
        using namespace BrahmaguptaSeries;
        return (2.0 * eccentricity) * sin(meanAnomaly) 
             + (1.25 * pow(eccentricity, 2)) * sin(2.0 * meanAnomaly);
    }

    void GeneratePanchanga(double jd) {
        double ayanamsha = VarahamihiraAyanamsha(jd);
        
        // Analytical Mean Longitudes (to be replaced by full VSOP87 series later)
        double sunMean = fmod(280.466 + 0.9856474 * (jd - 2451545.0), 360.0);
        double moonMean = fmod(218.316 + 13.176396 * (jd - 2451545.0), 360.0);
        
        // Applying the Ayanamsha to reach Nirayana (Sidereal) positions
        double sunNirayana = fmod(sunMean - ayanamsha + 360.0, 360.0);
        double moonNirayana = fmod(moonMean - ayanamsha + 360.0, 360.0);

        cout << "--- ARYABHATA PRECISION ENGINE ---" << endl;
        cout << fixed << setprecision(6);
        cout << "Ayanamsha:        " << ayanamsha << "°" << endl;
        cout << "Surya (Sun):      " << sunNirayana << "°" << endl;
        cout << "Chandra (Moon):   " << moonNirayana << "°" << endl;
        cout << "Nakshatra Index:  " << (int)(moonNirayana / (360.0/27.0)) + 1 << endl;
        cout << "-----------------------------------" << endl;
    }
};

int main() {
    AryabhataCore engine;
    // Calculation for April 5, 2026 (Julian Day 2461136.5)
    engine.GeneratePanchanga(2461136.5); 
    return 0;
}

