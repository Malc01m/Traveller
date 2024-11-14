#include "Actor.h"

typedef struct floraPart {
    bool hasPart;
    int partCount;
    int childCountTol;
    Color partColor;
    Color childColorTol;
    Group partGroup;
} floraPart;

class Flora : public Actor {
    public:
    private:

        // Genetics
        floraPart flower = {false, 3, 1, {0.5, 1, 0.3, 1}, {0.02, 0.02, 0.02, 0}, Group()};
/*
        bool doesFruiting = false;
        int fruitCount = 3;

        bool doesSeeding = true;
        int seedCount = 5;
        Color seedColor = {0, 0, 0, 1};
        Color seedColorTol = {0.1, 0.1, 0.1, 0};

        int leafCount = 30;
        Color leafColor = {0, 0, 0, 1};
        Color childLeafColorTol = {0.1, 0.1, 0.1, 0};

        double height = 0.2;
        double childHeightTol = 0.03;
        int rootStrength = 5;

        // Appearance
        Group stem;
        Group root;
        Group leaf;
        Group flower;
        Group fruit;
        Group seed;

        // Stats
        int energy;
*/
};