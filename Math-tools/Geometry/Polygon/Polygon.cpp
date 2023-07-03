#include "Polygon.h"
#include "GeometryInfo.h"

Polygon::Polygon(std::string name) {
    Polygon::name = name;
}

Polygon::Polygon(std::string name, std::vector<std::array<float, 2>> vertices, std::array<float, 4> color) {
    Polygon::name = name;
    Polygon::vertices = vertices;
    Polygon::color[0] = color[0];
    Polygon::color[1] = color[1];
    Polygon::color[2] = color[2];
    Polygon::color[3] = color[3];
}

Polygon::Polygon(const Polygon &poly) {
    name = poly.name;
    vertices = poly.vertices;
    color = poly.color;
}

void Polygon::setVertices(std::vector<std::array<float, 2>> vertices) {
    Polygon::vertices = vertices;
}

void Polygon::setColor(std::array<float, 4> color) {
    Polygon::color = color;
}

void Polygon::setName(std::string name) {
    Polygon::name = name;
}

bool Polygon::isVertexAt(int ind) {
    if (static_cast<int>(vertices.size()) > ind && ind >= 0) {
        return true;
    }
    return false;
}

std::vector<std::array<float, 2>> Polygon::getVertices() {
    return vertices;
}

std::array<float, 2> Polygon::getVertexAt(int ind) {
    if (isVertexAt(ind)) {
        return vertices.at(ind);
    }
    return {0, 0};
}

std::array<float, 4> Polygon::getColor() {
    return color;
}

void Polygon::addVertex(float x, float y) {
    vertices.push_back(std::array<float, 2>{x, y});
}
void Polygon::addVertex(std::array<float, 2> vert) {
    vertices.push_back(vert);
}

bool Polygon::removeVertex(int ind) {
    if ((ind >= 0) && (ind < static_cast<int>(vertices.size()))) {
        vertices.erase(vertices.begin() + ind);
        return true;
    } else {
        return false;
    }
}

bool Polygon::shiftVertex(int ind, int axis, float offset) {
    if (isVertexAt(ind)) {
        vertices.at(ind).at(axis) += offset;
        return true;
    }
    return false;
}

float Polygon::getMax(int axis) {
    return GeometryInfo::getMax(vertices, axis);
}

float Polygon::getMin(int axis) {
    return GeometryInfo::getMin(vertices, axis);
}

std::array<float, 2> Polygon::getCenter() {
    return GeometryInfo::getCenter(vertices);
}

void Polygon::rotate(std::array<float, 2> pivot, float angle) {
    vertices = GeometryInfo::rotate(vertices, pivot, angle);
}

void Polygon::shift(float offset, int axis) {
    vertices = GeometryInfo::shift(vertices, offset, axis);
}

void Polygon::shiftColor(std::array<float, 4> shiftColor) {
    for (unsigned int i = 0; i < color.size(); i++) {
        color[i] += shiftColor[i];
    }
}

void Polygon::shiftColorComponent(float shift, int component) {
    color[component] += shift;
}

void Polygon::shiftColorLightness(float shift) {
    color[0] += shift;
    color[1] += shift;
    color[2] += shift;
}

void Polygon::centerAt(float offset, int axis) {
    vertices = GeometryInfo::centerAt(vertices, offset, axis);
}

void Polygon::centerAt(std::array<float, 2> center) {
    centerAt(center.at(0), 0);
    centerAt(center.at(1), 1);
}

void Polygon::scale(std::array<float, 2> center, float factor, int axis) {
    vertices = GeometryInfo::scale(vertices, center, factor, axis);
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
    for (unsigned int j = 0; j < getVertices().size(); j++) {
        polyStatus.push_back("\t[Vertex " + std::to_string(j) + "]: (" + std::to_string(getVertices().at(j).at(0)) 
                                                        + ", "  + std::to_string(getVertices().at(j).at(1)) + ")");
    }
    return polyStatus;
}

std::vector<std::string> Polygon::getStatusColor(std::vector<std::string> polyStatus) {
    polyStatus.push_back("\t[Color]: (" + std::to_string(getColor().at(0)) + ", "
                                    + std::to_string(getColor().at(1)) + ", "
                                    + std::to_string(getColor().at(0)) + ")");
    return polyStatus;
}