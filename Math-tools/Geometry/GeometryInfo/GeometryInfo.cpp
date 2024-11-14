#include <math.h>

#include "GeometryInfo.h"
#include "Rand.h"

float GeometryInfo::getDist(Point point1, Point point2) {
    return sqrt(pow((point2.at(1) - point1.at(1)), 2) + pow((point2.at(0) - point1.at(0)), 2));
}

// Helper for getMax, getMin
float getExtreme(PointsPtr verts, bool tMaxfMin, int axis) {
    if (static_cast<int>(verts->size()) > 0) {
        float extr = verts->at(0)->at(axis);
        if (static_cast<int>(verts->size()) > 1) {
            for (unsigned int i = 0; i < verts->size(); i++) {
                float currVert = verts->at(i)->at(axis);
                if (tMaxfMin) {
                    if (extr < currVert) {
                        extr = currVert;
                    }
                } else {
                    if (extr > currVert) {
                        extr = currVert;
                    }
                }
            }
        }
        return extr;
    }
    return 0;
}

float GeometryInfo::getMax(PointsPtr verts, int axis) {
    return getExtreme(verts, true, axis);
}

float GeometryInfo::getMin(PointsPtr verts, int axis) {
    return getExtreme(verts, false, axis);
}

float GeometryInfo::getCenter(PointsPtr verts, int axis) {
    float center;
    float min = getExtreme(verts, false, axis);
    float max = getExtreme(verts, true, axis);
    center = ((max - min) / 2.0) + min;
    return center;
}

Point GeometryInfo::getCenter(PointsPtr verts) {
    Point center;
    center[0] = getCenter(verts, 0);
    center[1] = getCenter(verts, 1);
    return center;
}

Point GeometryInfo::getTopLeft(PointsPtr verts) {
    return {getMin(verts, 0), getMax(verts, 1)};
}

Point GeometryInfo::getTopRight(PointsPtr verts) {
    return {getMax(verts, 0), getMax(verts, 1)};
}

Point GeometryInfo::getBottomLeft(PointsPtr verts) {
    return {getMin(verts, 0), getMin(verts, 1)};
}

Point GeometryInfo::getBottomRight(PointsPtr verts) {
    return {getMin(verts, 0), getMax(verts, 1)};
}

Point GeometryInfo::getLeftCenter(PointsPtr verts) {
    return {getMin(verts, 0), getCenter(verts, 1)};
}

Point GeometryInfo::getRightCenter(PointsPtr verts) {
    return {getMax(verts, 0), getCenter(verts, 1)};
}

Point GeometryInfo::getTopCenter(PointsPtr verts) {
    return {getCenter(verts, 0), getMax(verts, 1)};
}

Point GeometryInfo::getBottomCenter(PointsPtr verts) {
    return {getCenter(verts, 0), getMin(verts, 1)};
}

float GeometryInfo::getAngle(Point point1, Point point2, Point pivot) {
    float ang1 = atan2(point1.at(1) - pivot.at(1), point1.at(0) - pivot.at(0));
    float ang2 = atan2(point2.at(1) - pivot.at(1), point2.at(0) - pivot.at(0));
    return std::abs(ang1 - ang2);
}

PointsPtr GeometryInfo::sortByNear(PointsPtr points) {
    PointsPtr sorted;
    PointsPtr remaining = points;
    PointPtr search = remaining->at(0);
    remaining->erase(remaining->begin());
    sorted->push_back(search);
    while (remaining->size() > 0) {
        int foundInd = 0;
        for (unsigned int j = 1; j < remaining->size(); j++) {
            if (getDist(*search, *remaining->at(j)) <
            getDist(*search, *remaining->at(foundInd))) {
                foundInd = j;
            }
        }
        sorted->push_back(remaining->at(foundInd));
        search = remaining->at(foundInd);
        remaining->erase(remaining->begin() + foundInd);
    }
    return sorted;
}

//TODO Finish zagSort
PointsPtr GeometryInfo::zagSort(PointsPtr points) {
    PointsPtr sorted;
    PointsPtr byNear = sortByNear(points);
    for (unsigned int i = 0; i < points->size() / 2; i++) {
        
    }
    throw("GemoetryInfo::zagSort: Not implemented");
}

Point GeometryInfo::rotate(Point point, Point pivot, float angle) {
    Point newPt;
    float radius = getDist(point, pivot);
    float prevAngle = atan2(point.at(1) - pivot.at(1), point.at(0) - pivot.at(0));
    newPt = {(cos(angle + prevAngle) * radius) + pivot.at(0), (sin(angle + prevAngle) * radius) + pivot.at(1)};
    return newPt;
}
PointsPtr GeometryInfo::rotate(PointsPtr verts, Point pivot, float angle) {
    for (unsigned int i = 0; i < verts->size(); i++) {
        *verts->at(i) = GeometryInfo::rotate(*verts->at(i), pivot, angle);
    }
    return verts;
}

Point GeometryInfo::shift(Point point, float offset, int axis) {
    point.at(axis) += offset;
    return point;
}

PointsPtr GeometryInfo::shift(PointsPtr verts, float offset, int axis) {
    for (unsigned int i = 0; i < verts->size(); i++) {
        *verts->at(i) = shift(*verts->at(i), offset, axis);
    }
    return verts;
}

Point GeometryInfo::shift(Point point, float offset, float angle) {
    point = rotate({offset + point.at(0), point.at(1)}, point, angle);
    return point;
}

PointsPtr GeometryInfo::shift(PointsPtr verts, float offset, float angle) {
    for (unsigned int i = 0; i < verts->size(); i++) {
        *verts->at(i) = shift(*verts->at(i), offset, angle);
    }
    return verts;
}

PointsPtr GeometryInfo::centerAt(
        PointsPtr verts, float offset, int axis) {
    float max = getExtreme(verts, true, axis);
    float min = getExtreme(verts, false, axis);
    float center = ((max - min) / 2.0) + min;
    #ifdef DEBUG
        std::cout << "GeometryInfo: Centering " << verts->size() << " vertices from (" << center << ") to (" 
            << offset << ") on axis " << axis << "\n";
    #endif
    for (unsigned int i = 0; i < verts->size(); i++) {
        #ifdef DEBUG
            std::cout << i << ": (" << verts->at(i)->at(0) << ", " << verts->at(i)->at(1) << ") -> ";
        #endif
        *verts->at(i) = shift(*(verts->at(i)), offset - center, axis);
        #ifdef DEBUG
            std::cout << "(" << verts->at(i)->at(0) << ", " << verts->at(i)->at(1) << ")\n";
        #endif
    }
    return verts;
}

PointsPtr GeometryInfo::centerAt(
        PointsPtr verts, Point offset) {
    #ifdef DEBUG
        std::cout << "GeometryInfo: Centering " << verts->size() << " vertices at (" 
            << offset.at(0) << ", " << offset.at(1) << ")\n";
    #endif
    verts = centerAt(verts, offset.at(0), 0);
    verts = centerAt(verts, offset.at(1), 1);
    return verts;
}

Point GeometryInfo::scale(Point point, Point center, float factor, int axis) {
    point.at(axis) = ((point.at(axis) - center.at(axis)) * factor) + center.at(axis);
    return point;
}

PointsPtr GeometryInfo::scale(PointsPtr verts, Point center, float factor, int axis) {
    for (unsigned int i = 0; i < verts->size(); i++) {
        *verts->at(i) = GeometryInfo::scale(*verts->at(i), center, factor, axis);
    }
    return verts;
}

PointsPtr GeometryInfo::radial(int numArms, float dist, float ang, float distScatter, float angScatter) {
    Point center = {0, 0};

    float angDiff = (2 * M_PI) / numArms;

    float minAng = angDiff - angScatter;
    float maxAng = angDiff + angScatter;
    float maxDist = dist + distScatter;
    float minDist = dist - distScatter;

    float thisAng = ang;
    float thisDist = Rand::randFloatBetween(minDist, maxDist);

    Point arm = GeometryInfo::shift(center, thisDist, thisAng);
    PointsPtr armVect = std::make_shared<std::vector<std::shared_ptr<Point>>>(
        std::vector<std::shared_ptr<Point>>()
    );
    std::shared_ptr<Point> armptr = std::make_shared<Point>(arm);
    armVect->push_back(armptr);

    for (int i = 1; i < numArms; i++) {
        thisAng = thisAng + Rand::randFloatBetween(minAng, maxAng);
        float thisDist = Rand::randFloatBetween(minDist, maxDist);
        Point arm = GeometryInfo::shift(center, thisDist, thisAng);
        armVect->push_back(std::make_shared<Point>(arm));
    }

    return armVect;
}
