#include <math.h>
#include <iostream>

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

Group GeometryGen::wheel(int numVerts, float radius, float ang, float radScatter, float angScatter) {
    std::array<float, 2> center = {0, 0};
    Group wheel("wheel");
    std::vector<std::array<float, 2>> armVect = 
        GeometryInfo::radial(numVerts, radius, ang, radScatter, angScatter);

    for (int i = 1; i < numVerts; i++) {
        Polygon centTri = Polygon("wheel triangle " + std::to_string(i));
        centTri.addVertex(center);
        centTri.addVertex(armVect.at(i - 1));
        centTri.addVertex(armVect.at(i));
        wheel.addPolygon(centTri);
    }

    Polygon centTri = Polygon("wheel closing triangle");
    centTri.addVertex(center);
    centTri.addVertex(armVect.at(armVect.size() - 1));
    centTri.addVertex(armVect.at(0));
    wheel.addPolygon(centTri);

    return wheel;
}

Group GeometryGen::tile(std::vector<std::array<float, 2>> coords) {
    throw("GeometryGen::tile: Not implemented");
}

Group GeometryGen::triFieldRadial(int iter, int initVerts, float avgDist, 
        float distScatter, float angScatter, float ringGrowthFactor) {

    // Use a wheel as center tris.
    Group triField = wheel(initVerts, avgDist, 0, distScatter, angScatter);
    triField.setName("trifield");

    // Get initial outer verts
    std::vector<std::array<float, 2>> lastOuter;
    for (int i = 0; i < triField.getNumPolygons(); i++) {
        lastOuter.push_back(triField.getPolygon(i)->getVertexAt(1));
    }

    float angCorrection = 0;
    for (int i = 2; i < iter + 2; i++) {
        // Create new outer vertex ring
        int numVerts = std::round(lastOuter.size() * ringGrowthFactor);
        std::vector<std::array<float, 2>> newOuter = 
            GeometryInfo::radial(numVerts, (avgDist * i), 0,
            distScatter, angScatter);
        
        // Distribute new vertices evenly to old vertices
        int vertRatio = newOuter.size() / lastOuter.size();
        int stray = newOuter.size() % lastOuter.size();

        std::vector<int> assign;
        for (int i = 0; i < lastOuter.size(); i++) {
            if (stray > 0) {
                assign.push_back(vertRatio + 1);
                stray = stray - 1;
            } else {
                assign.push_back(vertRatio);
            }
        }

        // Align new with last ring
        float avgSegs = newOuter.size() / (float)lastOuter.size();
        float angSegment = (M_PI * 2) / numVerts;
        angCorrection = angCorrection + (angSegment / 2) * avgSegs;
        newOuter = GeometryInfo::rotate(newOuter, {0, 0}, -angCorrection);

        // Connect old and new with tris
        int outerInd = 0;
        for (int j = 0; j < assign.size(); j++) {

            // Create number of vertex tris according to vals in assign
            for (int k = 0; k < assign.at(j); k++) {
                Polygon tri = Polygon("trifield iter " + std::to_string(i) + 
                    ", connect part " + std::to_string(outerInd) +
                    ", outer ring part " + std::to_string(j));
                tri.addVertex(lastOuter.at(j));
                tri.addVertex(newOuter.at(outerInd));
                tri.addVertex(newOuter.at((outerInd + 1) % newOuter.size()));
                triField.addPolygon(tri);

                outerInd++;
            }

            // When we've finished the vertex set, we need an edge tri
            Polygon tri = Polygon("trifield iter " + std::to_string(i) + 
                ", connect part " + std::to_string(outerInd) +
                ", outer ring part " + std::to_string(j));
            tri.addVertex(lastOuter.at(j));
            tri.addVertex(lastOuter.at((j + 1) % lastOuter.size()));
            tri.addVertex(newOuter.at(outerInd % newOuter.size()));
            triField.addPolygon(tri);

        }

        lastOuter = newOuter;
    }
    return triField;
}

Group GeometryGen::triTiles(float dist, int row, int col) {
    // Make tile patch
    float height = std::sqrt(std::pow(dist, 2) - std::pow(dist / 2, 2));
    Polygon rootTileOne = Polygon("triTile root 1");
    rootTileOne.addVertex(0, 0);
    rootTileOne.addVertex(dist, 0);
    rootTileOne.addVertex(dist / 2, height);
    Polygon rootTileTwo = Polygon("triTile root 2");
    rootTileTwo.addVertex(dist + (dist / 2), height);
    rootTileTwo.addVertex(dist, 0);
    rootTileTwo.addVertex(dist / 2, height);

    Group tilePatch = Group();
    tilePatch.addPolygon(rootTileOne);
    tilePatch.addPolygon(rootTileTwo);
    Group tiles = Group(tilePatch);

    for (int i = 0; i < col; i++) {
        
    }
    return tiles;
}