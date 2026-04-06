#include "../GrahaBase.hpp"

class Surya : public Graha {
public:
    Surya() {
        name = "Surya";
        physics = { 1.989e30, 695700, 7.25, 609.12, 0.0, "H, He" };
        metaphysics = { "Agni", "Sattva", {7} };
    }
};

