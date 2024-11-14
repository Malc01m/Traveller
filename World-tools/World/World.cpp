#include "World.h"
#include "GeometryGen.h"
#include "GeometryInfo.h"
#include "ColorMutators.h"
#include "Rand.h"

using namespace GeometryGen;
using namespace GeometryInfo;
using namespace ColorMutators;

World::World() {
    Group terrain = genTerrain();
    Group rocks = genRocks();
    worldGroup.addGroup(terrain);
    worldGroup.addGroup(rocks);

    scale(worldGroup, getCenter(terrain), 2, 0);
}

Group World::getWorldGroup() {
    return worldGroup;
}

void World::addActor(Actor actor) {
    actors.push_back(actor);
    worldGroup.addGroup(actor.getGroup());
}

Group World::genTerrain() {
    Group terrain = GeometryGen::triTiles(0.1, 40, 40, 0.05);
    terrain.setName("terrain");
    centerAt(terrain, {0, 0});

    Color terrainColor = {((float) 18 / 255), ((float) 212 / 255), ((float) 67 / 255), 1};
    terrain.setColors(terrainColor);
    scatterColorsLightness(terrain, 0.06);
    
    return terrain;
}

Group World::genRocks() {
    Group rocks("rocks");
    int numRocks = 30;
    for (int i = 0; i < numRocks; i++) {
        Group thisRock = GeometryGen::wheel(Rand::randIntBetween(3, 7), 0.1, 0, 0.05, 0.2);

        thisRock.setColors({((float) 100 / 255), ((float) 100 / 255), ((float) 107 / 255), 1});
        shift(thisRock, Rand::randFloatBetween(-2, 2), 0);
        shift(thisRock, Rand::randFloatBetween(-2, 2), 1);
        scatterColorsLightness(thisRock, 0.06);

        rocks.addGroup(thisRock);
    }
    return rocks;
}