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

    /**
     * @param verts Number of vertices
     * @param radius Distance from the center to a vertex
     * @returns A regular polygon
    */
    Polygon regularPoly(int verts, float radius);

    /**
     * @param coords Spherical coordinates of the tiling
     * @todo impelment
    */
    Group tile(std::vector<std::array<float, 2>> coords);

    /**
     * @brief Generates a group of triangles, each with a vertex at center,
     * that, when no scatter is applied, sums to a regular polygon.
     * 
     * @param numVerts Number of vertices in the composite regular polygon
     * @param radius Distance from center to outer vertices
     * @param ang Angle of first arm. Passed to radial.
     * @param radScatter Randomize the radius within this tolerance
     * @param angScatter Randomize the angle between outer vertices from 
     * center within this tolerance
    */
    Group wheel(int numVerts, float radius, float ang, float radScatter, float angScatter);

    /**
     * @brief Creates a tiling constructed of concentric rings of triangles.
     * @return an irregular triangular tiling
    */
    Group triFieldRadial(int iter, int initVerts, float avgDist, 
        float distScatter, float angScatter, float ringGrowthFactor);

    Group triTiles(float dist);
}

#endif