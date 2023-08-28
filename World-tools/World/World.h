#include "Group.h"

class World {
    public:
        World();
        Group getWorldGroup();
    private:
        Group genTerrain();
        Group worldGroup;
};