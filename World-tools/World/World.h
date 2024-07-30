#include "Actor.h"
#include "Group.h"

class World {
    public:

        World();
        Group getWorldGroup();
        void addActor(Actor actor);

    private:

        // Generation
        Group genTerrain();

        Group worldGroup;
        std::vector<Actor> actors = std::vector<Actor>();
};