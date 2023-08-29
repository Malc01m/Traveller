#include "World.h"
#include "GeometryGen.h"

World::World() {
    Group terrain = genTerrain();
    worldGroup.addGroup(terrain);
}

Group World::getWorldGroup() {
    return worldGroup;
}

Group World::genTerrain() {
    Group terrain = GeometryGen::triTiles(0.1, 5, 5);
    terrain.setColor({0.2, 1, 0, 1});
    terrain.scatterColorLightness(0.3);
    return terrain;
}