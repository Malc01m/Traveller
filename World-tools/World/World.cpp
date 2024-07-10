#include "World.h"
#include "GeometryGen.h"
#include "GeometryInfo.h"
#include "ColorMutators.h"

using namespace GeometryGen;
using namespace GeometryInfo;
using namespace ColorMutators;

World::World() {
    Group terrain = genTerrain();
    worldGroup.addGroup(terrain);
}

Group World::getWorldGroup() {
    return worldGroup;
}

Group World::genTerrain() {
    Group terrain = GeometryGen::triTiles(0.1, 20, 20, 0.05);
    centerAt(terrain, {0, 0});
    Color terrainColor = {((float) 18 / 255), ((float) 212 / 255), ((float) 67 / 255), 1};
    terrain.setColors(terrainColor);
    scatterColorsLightness(terrain, 0.06);
    scale(terrain, getCenter(terrain), 2, 0);
    return terrain;
}