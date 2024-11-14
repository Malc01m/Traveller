#include <math.h>
#include <iostream>

#include "GeometryInfo.h"
#include "GeometryGen.h"
#include "Rand.h"

using Point = std::array<float, 2>;

Point GeometryGen::randVert(float minx, float miny, float maxx, float maxy) {
    float x = Rand::randFloatBetween(minx, maxx);
    float y = Rand::randFloatBetween(miny, maxy);
    return {x, y};
}

std::vector<Point> GeometryGen::randVert(int number, float minx, float miny, float maxx, float maxy) {
    std::vector<Point> verts;
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
    Point center = {0, 0};
    Group wheel("wheel");
    
    PointsPtr armVect = 
        GeometryInfo::radial(numVerts, radius, ang, radScatter, angScatter);

    for (int i = 1; i < numVerts; i++) {
        Polygon centTri = Polygon("wheel triangle " + std::to_string(i));
        centTri.addVertex(center);
        centTri.addVertex(*armVect->at(i - 1));
        centTri.addVertex(*armVect->at(i));
        wheel.addPolygon(centTri);
    }

    Polygon centTri = Polygon("wheel closing triangle");
    centTri.addVertex(center);
    centTri.addVertex(*armVect->at(armVect->size() - 1));
    centTri.addVertex(*armVect->at(0));
    wheel.addPolygon(centTri);

    return wheel;
}

Group GeometryGen::tile(std::vector<Point> coords) {
    throw("GeometryGen::tile: Not implemented");
}

Group GeometryGen::triFieldRadial(int iter, int initVerts, float avgDist, 
        float distScatter, float angScatter, float ringGrowthFactor) {

    // Use a wheel as center tris.
    Group triField = wheel(initVerts, avgDist, 0, distScatter, angScatter);
    triField.setName("trifield");

    // Get initial outer verts
    PointsPtr lastOuter;
    for (int i = 0; i < triField.getNumPolygons(); i++) {
        lastOuter->push_back(std::make_shared<Point>(triField.getPolygon(i)->getVertexAt(1)));
    }

    float angCorrection = 0;
    for (int i = 2; i < iter + 2; i++) {
        // Create new outer vertex ring
        int numVerts = std::round(lastOuter->size() * ringGrowthFactor);
        PointsPtr newOuter = 
            GeometryInfo::radial(numVerts, (avgDist * i), 0,
            distScatter, angScatter);
        
        // Distribute new vertices evenly to old vertices
        int vertRatio = newOuter->size() / lastOuter->size();
        int stray = newOuter->size() % lastOuter->size();

        std::vector<int> assign;
        for (unsigned int i = 0; i < lastOuter->size(); i++) {
            if (stray > 0) {
                assign.push_back(vertRatio + 1);
                stray = stray - 1;
            } else {
                assign.push_back(vertRatio);
            }
        }

        // Align new with last ring
        float avgSegs = newOuter->size() / (float)lastOuter->size();
        float angSegment = (M_PI * 2) / numVerts;
        angCorrection = angCorrection + (angSegment / 2) * avgSegs;
        newOuter = GeometryInfo::rotate(newOuter, {0, 0}, -angCorrection);

        // Connect old and new with tris
        int outerInd = 0;
        for (unsigned int j = 0; j < assign.size(); j++) {

            // Create number of vertex tris according to vals in assign
            for (int k = 0; k < assign.at(j); k++) {
                Polygon tri = Polygon("trifield iter " + std::to_string(i) + 
                    ", connect part " + std::to_string(outerInd) +
                    ", outer ring part " + std::to_string(j));
                tri.addVertex(*lastOuter->at(j));
                tri.addVertex(*newOuter->at(outerInd));
                tri.addVertex(*newOuter->at((outerInd + 1) % newOuter->size()));
                triField.addPolygon(tri);

                outerInd++;
            }

            // When we've finished the vertex set, we need an edge tri
            Polygon tri = Polygon("trifield iter " + std::to_string(i) + 
                ", connect part " + std::to_string(outerInd) +
                ", outer ring part " + std::to_string(j));
            tri.addVertex(*lastOuter->at(j));
            tri.addVertex(*lastOuter->at((j + 1) % lastOuter->size()));
            tri.addVertex(*newOuter->at(outerInd % newOuter->size()));
            triField.addPolygon(tri);
        }

        lastOuter = newOuter;
    }
    return triField;
}

Group GeometryGen::triTiles(float dist, int rows, int cols, float scatter) {
    Group tiles;
    float height = std::sqrt(std::pow(dist, 2) - std::pow(dist / 2, 2));
    std::vector<Point> grid = pointGrid(height, 
        rows + 1, cols + 1, scatter);

    for (int i = 0; i < rows + 1; i++) {
        int rowOffset = ((rows + 1) * i);

        // Shift vertices of every other point row right
        if (i % 2 == 1) {
            for (int j = 0; j < cols + 1; j++) {
                grid.at(j + rowOffset) = {
                    grid.at(j + rowOffset).at(0) + (dist / 2),
                    grid.at(j + rowOffset).at(1)
                };
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        int rowOffset = ((rows + 1) * i);

        for (int j = 0; j < cols; j++) {
            Point sharedVert1;
            Point sharedVert2;
            Point tri1Vert;
            Point tri2Vert;

            if (i % 2 == 0) {
                sharedVert1 = grid.at(cols + 1 + j + rowOffset);
                sharedVert2 = grid.at(j + 1 + rowOffset);
                tri1Vert = grid.at(j + rowOffset);
                tri2Vert = grid.at(cols + 2 + j + rowOffset);
            } else {
                sharedVert1 = grid.at(j + rowOffset);
                sharedVert2 = grid.at(cols + 2 + j + rowOffset);
                tri1Vert = grid.at(cols + 1 + j + rowOffset);
                tri2Vert = grid.at(j + 1 + rowOffset);
            }

            Polygon tri1 = Polygon("TriTile at (" + std::to_string(j) + ", " 
                + std::to_string(i) + ", 1)");
            tri1.addVertex(sharedVert1);
            tri1.addVertex(sharedVert2);
            tri1.addVertex(tri1Vert);
            tiles.addPolygon(tri1);

            Polygon tri2 = Polygon("TriTile at (" + std::to_string(j) + ", " 
                + std::to_string(i) + ", 2)");
            tri2.addVertex(sharedVert1);
            tri2.addVertex(sharedVert2);
            tri2.addVertex(tri2Vert);
            tiles.addPolygon(tri2);
        }
    }
    return tiles;
}

std::vector<Point> GeometryGen::pointGrid(float dist, 
        int rows, int cols, float scatter) {

    std::vector<Point> grid;
    for (int i = 0; i < rows; i++) {
        float ypos = dist * i;
        for (int j = 0; j < cols; j++) {
            float xpos = dist * j;
            float xscatter = Rand::randFloatBetween(0, scatter);
            float yscatter = Rand::randFloatBetween(0, scatter);
            grid.push_back({xpos + xscatter, ypos + yscatter});
        }
    }
    return grid;
}