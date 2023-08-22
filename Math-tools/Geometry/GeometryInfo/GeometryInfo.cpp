#include <math.h>

#include "GeometryInfo.h"
#include "Rand.h"

float GeometryInfo::getDist(std::array<float, 2> point1, std::array<float, 2> point2) {
    return sqrt(pow((point2.at(1) - point1.at(1)), 2) + pow((point2.at(0) - point1.at(0)), 2));
}

// Helper for getMax, getMin
float getExtreme(std::vector<std::array<float, 2>> verts, bool tMaxfMin, int axis) {
    if (static_cast<int>(verts.size()) > 0) {
        float extr = verts.at(0).at(axis);
        if (static_cast<int>(verts.size()) > 1) {
            for (unsigned int i = 0; i < verts.size(); i++) {
                float currVert = verts.at(i).at(axis);
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

float GeometryInfo::getMax(std::vector<std::array<float, 2>> verts, int axis) {
    return getExtreme(verts, true, axis);
}

float GeometryInfo::getMin(std::vector<std::array<float, 2>> verts, int axis) {
    return getExtreme(verts, false, axis);
}

float GeometryInfo::getCenter(std::vector<std::array<float, 2>> verts, int axis) {
    float center;
    float min = getExtreme(verts, false, axis);
    float max = getExtreme(verts, true, axis);
    center = ((max - min) / 2.0) + min;
    return center;
}

std::array<float, 2> GeometryInfo::getCenter(std::vector<std::array<float, 2>> verts) {
    std::array<float, 2> center;
    center[0] = getCenter(verts, 0);
    center[1] = getCenter(verts, 1);
    return center;
}

std::array<float, 2> GeometryInfo::getTopLeft(std::vector<std::array<float, 2>> verts) {
    return {getMin(verts, 0), getMax(verts, 1)};
}

std::array<float, 2> GeometryInfo::getTopRight(std::vector<std::array<float, 2>> verts) {
    return {getMax(verts, 0), getMax(verts, 1)};
}

std::array<float, 2> GeometryInfo::getBottomLeft(std::vector<std::array<float, 2>> verts) {
    return {getMin(verts, 0), getMin(verts, 1)};
}

std::array<float, 2> GeometryInfo::getBottomRight(std::vector<std::array<float, 2>> verts) {
    return {getMin(verts, 0), getMax(verts, 1)};
}

std::array<float, 2> GeometryInfo::getLeftCenter(std::vector<std::array<float, 2>> verts) {
    return {getMin(verts, 0), getCenter(verts, 1)};
}

std::array<float, 2> GeometryInfo::getRightCenter(std::vector<std::array<float, 2>> verts) {
    return {getMax(verts, 0), getCenter(verts, 1)};
}

std::array<float, 2> GeometryInfo::getTopCenter(std::vector<std::array<float, 2>> verts) {
    return {getCenter(verts, 0), getMax(verts, 1)};
}

std::array<float, 2> GeometryInfo::getBottomCenter(std::vector<std::array<float, 2>> verts) {
    return {getCenter(verts, 0), getMin(verts, 1)};
}

float GeometryInfo::getAngle(std::array<float, 2> point1, std::array<float, 2> point2, std::array<float, 2> pivot) {
    float ang1 = atan2(point1.at(1) - pivot.at(1), point1.at(0) - pivot.at(0));
    float ang2 = atan2(point2.at(1) - pivot.at(1), point2.at(0) - pivot.at(0));
    return std::abs(ang1 - ang2);
}

std::vector<std::array<float, 2>> GeometryInfo::sortByNear(std::vector<std::array<float, 2>> points) {
    std::vector<std::array<float, 2>> sorted;
    std::vector<std::array<float, 2>> remaining = points;
    std::array<float, 2> search = remaining.at(0);
    remaining.erase(remaining.begin());
    sorted.push_back(search);
    while (remaining.size() > 0) {
        int foundInd = 0;
        for (unsigned int j = 1; j < remaining.size(); j++) {
            if (getDist(search, remaining.at(j)) <
            getDist(search, remaining.at(foundInd))) {
                foundInd = j;
            }
        }
        sorted.push_back(remaining.at(foundInd));
        search = remaining.at(foundInd);
        remaining.erase(remaining.begin() + foundInd);
    }
    return sorted;
}

//TODO Finish zagSort
std::vector<std::array<float, 2>> GeometryInfo::zagSort(std::vector<std::array<float, 2>> points) {
    std::vector<std::array<float, 2>> sorted;
    std::vector<std::array<float, 2>> byNear = sortByNear(points);
    for (unsigned int i = 0; i < points.size() / 2; i++) {
        
    }
    throw("GemoetryInfo::zagSort: Not implemented");
}

std::array<float, 2> GeometryInfo::rotate(std::array<float, 2> point, std::array<float, 2> pivot, float angle) {
    std::array<float, 2> newPt;
    float radius = getDist(point, pivot);
    float prevAngle = atan2(point.at(1) - pivot.at(1), point.at(0) - pivot.at(0));
    newPt = {(cos(angle + prevAngle) * radius) + pivot.at(0), (sin(angle + prevAngle) * radius) + pivot.at(1)};
    return newPt;
}
std::vector<std::array<float, 2>> GeometryInfo::rotate(std::vector<std::array<float, 2>> verts, std::array<float, 2> pivot, float angle) {
    for (unsigned int i = 0; i < verts.size(); i++) {
        verts.at(i) = GeometryInfo::rotate(verts.at(i), pivot, angle);
    }
    return verts;
}

std::array<float, 2> GeometryInfo::shift(std::array<float, 2> point, float offset, int axis) {
    point.at(axis) += offset;
    return point;
}

std::vector<std::array<float, 2>> GeometryInfo::shift(std::vector<std::array<float, 2>> verts, float offset, int axis) {
    for (unsigned int i = 0; i < verts.size(); i++) {
        verts.at(i) = shift(verts.at(i), offset, axis);
    }
    return verts;
}

std::array<float, 2> GeometryInfo::shift(std::array<float, 2> point, float offset, float angle) {
    point = rotate({offset + point.at(0), point.at(1)}, point, angle);
    return point;
}

std::vector<std::array<float, 2>> GeometryInfo::shift(std::vector<std::array<float, 2>> verts, float offset, float angle) {
    for (unsigned int i = 0; i < verts.size(); i++) {
        verts.at(i) = shift(verts.at(i), offset, angle);
    }
    return verts;
}

std::vector<std::array<float, 2>> GeometryInfo::centerAt(std::vector<std::array<float, 2>> verts, float offset, int axis) {
    float max = getExtreme(verts, true, axis);
    float min = getExtreme(verts, false, axis);
    float center = ((max - min) / 2.0) + min;
    for (unsigned int i = 0; i < verts.size(); i++) {
        verts.at(i) = shift(verts.at(i), offset - center, axis);
    }
    return verts;
}

std::array<float, 2> GeometryInfo::scale(std::array<float, 2> point, std::array<float, 2> center, float factor, int axis) {
    point.at(axis) = ((point.at(axis) - center.at(axis)) * factor) + center.at(axis);
    return point;
}

std::vector<std::array<float, 2>> GeometryInfo::scale(std::vector<std::array<float, 2>> verts, std::array<float, 2> center, float factor, int axis) {
    for (unsigned int i = 0; i < verts.size(); i++) {
        verts.at(i) = GeometryInfo::scale(verts.at(i), center, factor, axis);
    }
    return verts;
}

std::vector<std::array<float, 2>> GeometryInfo::radial(int numArms, float dist, float ang, float distScatter, float angScatter) {
    std::array<float, 2> center = {0, 0};

    float angDiff = (2 * M_PI) / numArms;

    float minAng = angDiff - angScatter;
    float maxAng = angDiff + angScatter;
    float maxDist = dist + distScatter;
    float minDist = dist - distScatter;

    float thisAng = ang;
    float thisDist = Rand::randFloatBetween(minDist, maxDist);

    std::array<float, 2> arm = GeometryInfo::shift(center, thisDist, thisAng);
    std::vector<std::array<float, 2>> armVect = {arm};

    for (int i = 1; i < numArms; i++) {
        thisAng = thisAng + Rand::randFloatBetween(minAng, maxAng);
        float thisDist = Rand::randFloatBetween(minDist, maxDist);
        std::array<float, 2> arm = GeometryInfo::shift(center, thisDist, thisAng);
        armVect.push_back(arm);
    }

    return armVect;
}
