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

Group GeometryGen::triField(int iter, float avgDist, float distScatter, 
        float angScatter) {

    // Use a wheel as center tris.
    int numVerts = Rand::randIntBetween(3, 5);
    int ang = Rand::randFloatBetween(0, 2 * M_PI);
    Group triField = wheel(numVerts, avgDist, ang, distScatter, angScatter);
    triField.setName("trifield");

    // Get initial outer verts
    std::vector<std::array<float, 2>> outerVerts;
    for (int i = 0; i < triField.getNumPolygons(); i++) {
        outerVerts.push_back(triField.getPolygon(i)->getVertexAt(1));
    }

    for (int i = 2; i < iter + 2; i++) {
        // Create new outer vertex ring
        int numVerts = Rand::randIntBetween(outerVerts.size(), (5 * i));
        std::vector<std::array<float, 2>> newOuter = 
            GeometryInfo::radial(numVerts, (avgDist * i), ang,
            distScatter, angScatter);
        
        // Distribute new vertices evenly to old vertices
        int vertRatio = newOuter.size() / outerVerts.size();
        int stray = newOuter.size() % outerVerts.size();
        std::vector<int> assign;
        for (int i = 0; i < outerVerts.size(); i++) {
            if (stray > 0) {
                assign.push_back(vertRatio + 1);
                stray = stray - 1;
            } else {
                assign.push_back(vertRatio);
            }
        }

        // Connect old and new
        int newInd = 0;
        for (int j = 0; j < outerVerts.size(); j++) {
            int connect = assign.back();
            assign.pop_back();

            for (int k = 0; k < connect; k++) {
                Polygon tri = Polygon("trifield iter " + std::to_string(i) + 
                    ", connect part " + std::to_string(k) +
                    ", outer ring part " + std::to_string(newInd));
                tri.addVertex(outerVerts.at(j));
                if (newOuter.size() < newInd + 1) {
                    tri.addVertex(newOuter.at(newInd));
                    tri.addVertex(newOuter.at(newInd + 1));
                } else {
                    // Seems to produce flipped normal?
                    tri.addVertex(newOuter.at(0));
                    tri.addVertex(newOuter.at(newInd));
                }
                triField.addPolygon(tri);
                newInd++;
            }
        }

        outerVerts = newOuter;
    }
    return triField;
}