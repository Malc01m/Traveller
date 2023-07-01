#ifndef GEOMETRYINFO_H
#define GEOMETRYINFO_H

#include <array>
#include <vector>

namespace GeometryInfo {

    //Pointset info

    /**
     * @brief Gets the distance between two points
     * 
     * @param point1 the first point
     * @param point2 the second point
     * @return the distance between two points
     */
    float getDist(std::array<float, 2> point1, std::array<float, 2> point2);

    /**
     * @brief Gets the largest or smallest value on one axis in a set of vertices
     * 
     * @param verts The vertices to search through
     * @param tMaxfMin True if looking for a maximum, false if looking for a minimum.
     * @param axis The axis to search on. 0 is x, 1 is y.
     * @return the largest or smallest value on the given axis in verts
     */
    float getExtreme(std::vector<std::array<float, 2>> verts, bool tMaxfMin, int axis);

    /**
     * @return the angle between point1 and point2 with respect to pivot
    */
    float getAngle(std::array<float, 2> point1, std::array<float, 2> point2, std::array<float, 2> pivot);

    /**
     * @return the center of verts on an axis
    */
    float getCenter(std::vector<std::array<float, 2>> verts, int axis);
    
    /**
     * @return the center of verts on both axes
    */
    std::array<float, 2> getCenter(std::vector<std::array<float, 2>> verts);

    std::array<float, 2> getTopLeft(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getTopRight(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getBottomLeft(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getBottomRight(std::vector<std::array<float, 2>> verts);

    std::array<float, 2> getLeftCenter(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getRightCenter(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getTopCenter(std::vector<std::array<float, 2>> verts);
    std::array<float, 2> getBottomCenter(std::vector<std::array<float, 2>> verts);

    //Returns the vector of points reordered by closeness
    std::vector<std::array<float, 2>> sortByNear(std::vector<std::array<float, 2>> points);

    //Returns the vector of points zigzagged by closeness
    std::vector<std::array<float, 2>> zagSort(std::vector<std::array<float, 2>> points);

    //Transformations

    //Rotate

    //Rotates the point by angle in radians around the pivot
    std::array<float, 2> rotate(std::array<float, 2> point, std::array<float, 2> pivot, float angle);
    //Rotates all points by angle in radians around the pivot
    std::vector<std::array<float, 2>> rotate(std::vector<std::array<float, 2>> verts, std::array<float, 2> pivot, float angle);

    //Shift

    //Shifts the point on axis by offset
    std::array<float, 2> shift(std::array<float, 2> point, float offset, int axis);
    //Shifts all vertices on axis by offset
    std::vector<std::array<float, 2>> shift(std::vector<std::array<float, 2>> verts, float offset, int axis);
    //Shifts the point at angle by offset
    std::array<float, 2> shift(std::array<float, 2> point, float offset, float angle);
    //Shifts all points at angle by offset
    std::vector<std::array<float, 2>> shift(std::vector<std::array<float, 2>> verts, float offset, float angle);

    //Center at

    //Shifts all verticess on axis to be centered around cntr
    std::vector<std::array<float, 2>> centerAt(std::vector<std::array<float, 2>> verts, float offset, int axis);

    //Scale

    //Scales the point around center on axis by factor
    std::array<float, 2> scale(std::array<float, 2> point, std::array<float, 2> center, float factor, int axis);
    //Scales all verticess around center on axis by factor
    std::vector<std::array<float, 2>> scale(std::vector<std::array<float, 2>> verts, std::array<float, 2> center, float factor, int axis);

}

#endif