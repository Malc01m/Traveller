#include "Group.h"

class Actor {
    public:
        Actor();
        Group getGroup();
    private:
        Group actorGroup;

        bool Visible;
        std::vector<Color> Colors;
        // Physical
        double Mass;
        double Density;
        // Chemical
        double Temperature;
        double Acidity;
        double Toxicity;
};