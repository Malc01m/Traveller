#ifndef GEOMETRYGEN_H
#define GEOMETRYGEN_H

#include <array>

#include "Polygon.h"
#include "Group.h"

namespace GeometryGen {

    /**
     * @returns A random vertex within the given bounds
    */
    std::array<float, 2> randVert(float minx, float miny, float maxx, float maxy);

    /**
     * @returns The requested number of random vertices within the given bounds
    */
    std::vector<std::array<float, 2>> randVert(int number, float minx, float miny, 
        float maxx, float maxy);

    // Returns a regular polygon with the specified number of vertices each at a distance 
    // equal to radius from the center
    /**
     * @returns a regular polygon with the specified number of vertices each at a distance 
     * equal to radius from the center
    */
    Polygon regularPoly(int verts, float radius);

    // Group generators
    Group tile(std::vector<std::array<float, 2>> coords);

    Group triField(int iter, float avgDist, float distScatter, float angScatter);
}

#endif