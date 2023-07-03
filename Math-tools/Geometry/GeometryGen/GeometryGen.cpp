#include <math.h>

#include "GeometryInfo.h"
#include "GeometryGen.h"
#include "Rand.h"

std::array<float, 2> GeometryGen::randVert(float minx, float miny, float maxx, float maxy) {
    float x = Rand::randFloatBetween(minx, maxx);
    float y = Rand::randFloatBetween(miny, maxy);
    return {x, y};
}

std::vector<std::array<float, 2>> GeometryGen::randVert(int number, float minx, float miny, float maxx, float maxy) {
    std::vector<std::array<float, 2>> verts;
    for (int i = 0; i < number; i++) {
        verts.push_back(randVert(minx, miny, maxx, maxy));
    }
    return verts;
}

Polygon GeometryGen::regularPoly(int verts, float radius) {
    Polygon c("regPoly");
    float angleDifference = (2 * M_PI) / verts;
    for (int i = 0; i < (verts / 2) + 1; i++) {
        float y = cos(angleDifference * i) * radius;
        float x = sin(angleDifference * i) * radius;
        c.addVertex(x, y);
        //Top vertex never gets a mirror vertex. 
        //The bottom vertex (half+1) of an even polygon doesn't get a mirror vertex.
        if ((i != 0) && ((verts % 2 != 0) || (i != (verts / 2)))) { 
            c.addVertex(-x, y);
        }
    }
    return c;
}

Group GeometryGen::tile(std::vector<std::array<float, 2>> coords) {
    throw("GeometryGen::tile: Not implemented");
}

Group GeometryGen::triField(int iter, float avgDist, float distScatter, float angScatter) {
    std::array<float, 2> center = {0, 0};
    Group triField("triField");
    int numVerts = Rand::randIntBetween(3, 5);
    float angDiff = (2 * M_PI) / numVerts;
    float minAng = angDiff - angScatter;
    float maxAng = angDiff + angScatter;
    float maxDist = avgDist + distScatter;
    float minDist = avgDist - distScatter;

    // Choose a random angle to start
    float thisAng = Rand::randFloatBetween(0, 2 * M_PI);
    float dist = Rand::randFloatBetween(minDist, maxDist);
    std::array<float, 2> arm = GeometryInfo::shift(center, dist, thisAng);
    std::vector<std::array<float, 2>> armVect = {arm};

    for (int i = 1; i < numVerts; i++) {
        float thisAng = thisAng + Rand::randFloatBetween(minAng, maxAng);
        float dist = Rand::randFloatBetween(minDist, maxDist);
        std::array<float, 2> arm = GeometryInfo::shift(center, dist, thisAng);
        Polygon centTri = Polygon("triField central triangle " + std::to_string(i));
        centTri.addVertex(center);
        centTri.addVertex(arm);
        centTri.addVertex(armVect.at(armVect.size() - 1));
        triField.addPolygon(centTri);

        armVect.push_back(arm);
    }

    Polygon centTri = Polygon("triField closing central triangle");
    centTri.addVertex(center);
    centTri.addVertex(armVect.at(armVect.size() - 1));
    centTri.addVertex(armVect.at(1));
    triField.addPolygon(centTri);

    return triField;
}