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
    Group terrain = GeometryGen::triTiles(0.1, 20, 20, 0.05);
    terrain.centerAt({0, 0});
    terrain.setColor({((float) 18 / 255), ((float) 212 / 255), ((float) 67 / 255), 1});
    terrain.scatterColorLightness(0.06);
    terrain.scale(2, 0);
    return terrain;
}