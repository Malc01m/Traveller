#include "GridGroup.h"
#include "GeometryInfo.h"

GridGroup::GridGroup() : Group("Grid") {}

GridGroup::GridGroup(float xSpacing, float ySpacing, float xAxisAng, float yAxisAng) : Group("Grid") {
    GridGroup::xSpacing = xSpacing;
    GridGroup::ySpacing = ySpacing;
    GridGroup::xAxisAng = xAxisAng;
    GridGroup::yAxisAng = yAxisAng;
}

GridGroup::GridGroup(std::string name, float xSpacing, float ySpacing, float xAxisAng, float yAxisAng) : 
GridGroup(xSpacing, ySpacing, xAxisAng, yAxisAng) {
    this->setName(name);
}

void GridGroup::fill(Polygon poly, int startx, int starty, int endx, int endy) {
    for (int i = startx; i <= endx; i++) {
        for (int j = starty; j <= endy; j++) {
            addPolygon(poly, i, j);
        }
    }
    alignAll();
}

void GridGroup::addPolygon(Polygon poly, int x, int y) {
    addPolygon(std::make_shared<Polygon>(poly), x, y);
}

void GridGroup::addPolygon(std::shared_ptr<Polygon> poly, int x, int y) {
    polys.push_back(poly);
    coords.push_back(std::make_tuple<int, float, float>(polys.size() - 1, x, y));
    align(poly, x, y);
}

void GridGroup::align(std::shared_ptr<Polygon> poly, float x, float y) {
    float xDist = x * xSpacing;
    float yDist = y * ySpacing;
    std::array<float, 2> xpath = GeometryInfo::rotate({xDist, 0}, {0, 0}, xAxisAng);
    std::array<float, 2> ypath = GeometryInfo::rotate({yDist, 0}, {0, 0}, yAxisAng);
    std::array<float, 2> path = {xpath.at(0) + ypath.at(0) + origin[0], xpath.at(1) + ypath.at(1) + origin[1]}; 
    poly->centerAt(path);
}

void GridGroup::alignAll() {
    for (unsigned int i = 0; i < coords.size(); i++) {
        int index = std::get<0>(coords.at(i));
        if ((index > 0) && (index < static_cast<int>(polys.size()))) {
            align(polys.at(index), std::get<1>(coords.at(i)), std::get<2>(coords.at(i)));
        }
    }
}

void GridGroup::setXSpacing(float xSpacing) {
    GridGroup::xSpacing = xSpacing;
    alignAll();
}

void GridGroup::setYSpacing(float ySpacing) {
    GridGroup::ySpacing = ySpacing;
    alignAll();
}

void GridGroup::setXAxisAng(float xAxisAng) {
    GridGroup::xAxisAng = xAxisAng;
    alignAll();
}

void GridGroup::setYAxisAng(float yAxisAng){
    GridGroup::yAxisAng = yAxisAng;
    alignAll();
}

void GridGroup::shift(float offset, int axis, bool moveOrigin) {
    Group::shift(offset, axis);
    if (moveOrigin) {
        origin[axis] += offset;
    }
}