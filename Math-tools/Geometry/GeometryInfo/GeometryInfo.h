#ifndef GEOMETRYINFO_H
#define GEOMETRYINFO_H

#include <array>
#include <vector>
#include <memory>
#include <iostream>

using Point = std::array<float, 2>;
using PointPtr = std::shared_ptr<Point>;
using PointsPtr = std::shared_ptr<std::vector<PointPtr>>;

namespace GeometryInfo {

    //Pointset info

    /**
     * @brief Gets the distance between two points
     * 
     * @param point1 the first point
     * @param point2 the second point
     * @return the distance between two points
     */
    float getDist(Point point1, Point point2);

    /**
     * @brief Gets the smallest value on one axis in a set of vertices
     * 
     * @param verts The vertices to search through
     * @param axis The axis to search on. 0 is x, 1 is y.
     * @return the smallest value on the given axis in verts
     */
    float getMin(PointsPtr verts, int axis);

    /**
     * @brief Gets the largest value on one axis in a set of vertices
     * 
     * @param verts The vertices to search through
     * @param axis The axis to search on. 0 is x, 1 is y.
     * @return the largest value on the given axis in verts
     */
    float getMax(PointsPtr verts, int axis);

    /**
     * @return the angle between point1 and point2 with respect to pivot
    */
    float getAngle(Point point1, Point point2, Point pivot);

    /**
     * @return the center of verts on an axis
    */
    float getCenter(PointsPtr verts, int axis);
    
    /**
     * @return the center of verts on both axes
    */
    Point getCenter(PointsPtr verts);

    Point getTopLeft(PointsPtr verts);
    Point getTopRight(PointsPtr verts);
    Point getBottomLeft(PointsPtr verts);
    Point getBottomRight(PointsPtr verts);

    Point getLeftCenter(PointsPtr verts);
    Point getRightCenter(PointsPtr verts);
    Point getTopCenter(PointsPtr verts);
    Point getBottomCenter(PointsPtr verts);

    //Returns the vector of points reordered by closeness
    PointsPtr sortByNear(
        PointsPtr points);

    //Returns the vector of points zigzagged by closeness
    PointsPtr zagSort(
        PointsPtr points);

    //Transformations

    //Rotate

    //Rotates the point by angle in radians around the pivot
    Point rotate(Point point, 
        Point pivot, float angle);
    //Rotates all points by angle in radians around the pivot
    PointsPtr rotate(
        PointsPtr verts, Point pivot, 
        float angle);

    //Shift

    //Shifts the point on axis by offset
    Point shift(Point point, float offset, 
        int axis);
    //Shifts all vertices on axis by offset
    PointsPtr shift(
        PointsPtr verts, float offset, int axis);
    //Shifts the point at angle by offset
    Point shift(Point point, float offset, 
        float angle);
    //Shifts all points at angle by offset
    PointsPtr shift(
        PointsPtr verts, float offset, float angle);

    //Center at

    //Shifts all verticess on axis to be centered around cntr
    PointsPtr centerAt(
        PointsPtr verts, float offset, int axis);
    PointsPtr centerAt(
        PointsPtr verts, Point offset);

    //Scale

    //Scales the point around center on axis by factor
    Point scale(Point point, 
        Point center, float factor, int axis);
    //Scales all verticess around center on axis by factor
    PointsPtr scale(
        PointsPtr verts, Point center, 
        float factor, int axis);

    // Formations
    /**
     * @brief Creates a formation of points around a center
     * @returns a vector of point arrays 
    */
    PointsPtr radial(int numArms, float dist, float ang, 
        float distScatter, float angScatter);

}

#endif