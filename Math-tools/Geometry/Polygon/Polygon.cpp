#include "Polygon.h"
#include "GeometryInfo.h"

Polygon::Polygon() {}

Polygon::Polygon(std::string name) {
    Polygon::name = name;
}

Polygon::Polygon(std::string name, PointsPtr vertices, Color color) {
    Polygon::name = name;
    Polygon::vertices = vertices;
    Polygon::color->at(0) = color[0];
    Polygon::color->at(1) = color[1];
    Polygon::color->at(2) = color[2];
    Polygon::color->at(3) = color[3];
}

Polygon::Polygon(const Polygon &poly) {
    name = poly.name;
    vertices = poly.vertices;
    color = poly.color;
}

void Polygon::setVertices(PointsPtr vertices) {
    Polygon::vertices = vertices;
}

void Polygon::setColor(Color color) {
    Polygon::color = std::make_shared<Color>(color);
}

void Polygon::setName(std::string name) {
    Polygon::name = name;
}

bool Polygon::isVertexAt(int ind) {
    if (static_cast<int>(vertices->size()) > ind && ind >= 0) {
        return true;
    }
    return false;
}

PointsPtr Polygon::getVertices() {
    return vertices;
}

Point Polygon::getVertexAt(int ind) {
    if (isVertexAt(ind)) {
        return *vertices->at(ind);
    }
    return {0, 0};
}

void Polygon::decoupleVerts() {
    PointsPtr newVerts = std::make_shared<std::vector<PointPtr>>();
    for (unsigned int i = 0; i < vertices->size(); i++) {
        newVerts->push_back(std::make_shared<Point>(*vertices->at(i)));
    }
    vertices = newVerts;
}

Color Polygon::getColor() {
    return *color;
}

ColorPtr Polygon::getColorPtr() {
    return color;
}

void Polygon::addVertex(float x, float y) {
    vertices->push_back(std::make_shared<Point>(Point{x, y}));
}
void Polygon::addVertex(Point vert) {
    vertices->push_back(std::make_shared<Point>(vert));
}

bool Polygon::removeVertex(int ind) {
    if ((ind >= 0) && (ind < static_cast<int>(vertices->size()))) {
        vertices->erase(vertices->begin() + ind);
        return true;
    } else {
        return false;
    }
}

bool Polygon::shiftVertex(int ind, int axis, float offset) {
    if (isVertexAt(ind)) {
        vertices->at(ind)->at(axis) += offset;
        return true;
    }
    return false;
}

void Polygon::shiftColor(std::array<float, 4> shiftColor) {
    for (unsigned int i = 0; i < color->size(); i++) {
        color->at(i) += shiftColor[i];
    }
}

void Polygon::shiftColorComponent(float shift, int component) {
    color->at(component) += shift;
}

void Polygon::shiftColorLightness(float shift) {
    color->at(0) += shift;
    color->at(1) += shift;
    color->at(2) += shift;
}

void Polygon::decoupleColor() {
    color = std::make_shared<Color>(*color);
}

void Polygon::printStatus() {
    std::vector<std::string> polyStat = getStatus();
    for (unsigned int i = 0; i < polyStat.size(); i++) {
        std::cout << polyStat.at(i) << '\n';
    }
}

std::vector<std::string> Polygon::getStatus() {
    //TODO: Complete status with vertices and color
    std::vector<std::string> polyStatus;
    polyStatus.push_back("[Polygon] " + name + ":");
    polyStatus = getStatusVertices(polyStatus);
    polyStatus = getStatusColor(polyStatus);
    return polyStatus;
}

std::vector<std::string> Polygon::getStatus(int num) {
    //TODO: Complete status with vertices and color
    std::vector<std::string> polyStatus;
    polyStatus.push_back("[Polygon " + std::to_string(num) + "] " + name + ":");
    polyStatus = getStatusVertices(polyStatus);
    polyStatus = getStatusColor(polyStatus);
    return polyStatus;
}

std::vector<std::string> Polygon::getStatusVertices(std::vector<std::string> polyStatus) {
    for (unsigned int j = 0; j < getVertices()->size(); j++) {
        polyStatus.push_back("\t[Vertex " + std::to_string(j) + "]: (" + std::to_string(getVertices()->at(j)->at(0)) 
                                                        + ", "  + std::to_string(getVertices()->at(j)->at(1)) + ")");
    }
    return polyStatus;
}

std::vector<std::string> Polygon::getStatusColor(std::vector<std::string> polyStatus) {
    polyStatus.push_back("\t[Color]: (" + std::to_string(getColor().at(0)) + ", "
                                    + std::to_string(getColor().at(1)) + ", "
                                    + std::to_string(getColor().at(0)) + ")");
    return polyStatus;
}