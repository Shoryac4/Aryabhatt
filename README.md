# Aryabhatt Engine v1.0

An ultra-lightweight, standalone C++ astronomical engine designed for high-precision Vedic calculations, planetary positions (Sayana & Nirayana), and local Horizon events. Unlike the Swiss Ephemeris, this engine is entirely self-contained and requires no external data files or Internet access.

## 🚀 Features
- **Nirayana Mapping:** High-accuracy conversion to Nakshatras, Padas, and Rashis using the Lahiri Ayanamsha.
- **Horizon Module:** Binary-search based Sunrise/Sunset calculation with elevation-based atmospheric dip and refraction.
- **Kala-Velas:** Precise local timings for Mandi and Gulika based on weekday segments.
- **Zero Dependencies:** Compiles directly with G++ without external libraries.
- **Mobile First:** Optimized for low-memory environments (runs on 4GB RAM devices via Termux).

## 📂 Project Structure
```text
Aryabhatt_Home/
├── src/
│   └── main.cpp            # Entry point and CLI interface
├── include/
│   ├── AryabhataCore.hpp   # Core astronomical blueprints
│   ├── Sages/
│   │   ├── Horizon.hpp     # Header for Horizon math
│   │   └── Horizon.cpp     # Implementation of Sunrise/Sunset/Kala-Velas
│   └── BrahmaguptaMath.cpp # Keplerian orbital elements and perturbation logic
└── Aryabhatt               # Binary (generated after compilation)

🛠️ Installation & Compilation
1. Prerequisites
Ensure you have a C++ compiler installed. In Termux, run:
pkg install clang g++ make

*2. Clone and Compile*
Navigate to your project root and run the following command:
g++ -O3 src/main.cpp include/Sages/*.cpp -I include -o Aryabhatt
Note: The -O3 flag enables aggressive optimization for maximum execution speed.

**3. Usage**
Run the engine to get live tracking data for your current system time:
./Aryabhatt

📍 Customization
To change the observer location (currently set to Vikasnagar, Uttarakhand), edit the ObserverLocation struct in src/main.cpp
localObserver.latitude = 30.34;   // Your Latitude
localObserver.longitude = 77.75;  // Your Longitude
localObserver.tzOffset = 5.5;     // Your Timezone (IST = +5.5)

Other features
Planetary degree - ±1' to 5' Arcminutes
Logic - Analytical/ keplerian/ Panchanga
Data Dependencies - None

⚖️ License
Open Source under MIT License. Feel free to use, modify, and integrate into your own apps.
Developed by: Samraat Chauhan
Project: Vedic Universal Frequencies & Vibrations Research
Special thanks for support -1. Mr A. K. Chauhan
                            2. Pinki Bhatt
                            3. Preetam Tomar
