#include <fstream>
#include <iostream>

#include "Group.h"
#include "GeometryInfo.h"

Group::Group() {
    
}

Group::Group(Polygon poly) {
    addPolygon(poly);
}

Group::Group(std::string name) {
    Group::name = name;
}

Group::Group(std::string name, Polygon poly) {
    Group::name = name;
    addPolygon(poly);
}

Group::Group(std::string name, std::vector<std::shared_ptr<Polygon>> polys) {
    Group::name = name;
    Group::polys = polys;
}

Group::Group(std::vector<std::shared_ptr<Polygon>> polys) {
    Group::polys = polys;
}

void Group::setName(std::string name) {
    Group::name = name;
}

void Group::addPolygon(std::shared_ptr<Polygon> poly) {
    polys.push_back(poly);
}

void Group::addPolygon(Polygon poly) {
    polys.push_back(std::make_shared<Polygon>(poly));
}

void Group::addPolygons(std::vector<std::shared_ptr<Polygon>> polys) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        Group::polys.push_back(polys.at(i));
    }
}

void Group::removePolygon(std::shared_ptr<Polygon> poly) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        if (polys.at(i).get() == poly.get()) {
            polys.erase(polys.begin() + i);
        }
    }
}

void Group::empty() {
    if (polys.size() > 0) {
        polys = std::vector<std::shared_ptr<Polygon>>();
    }
}

void Group::setPolygons(std::vector<std::shared_ptr<Polygon>> polys) {
    Group::polys = polys;
}

void Group::setPolygons(std::vector<Polygon> polys) {
    std::vector<std::shared_ptr<Polygon>> newpolys;
    for (unsigned int i = 0; i < polys.size(); i++) {
        newpolys.push_back(std::make_shared<Polygon>(polys.at(i)));
    }
    Group::polys = newpolys;
}

bool Group::isPolygonAt(int ind) {
    return (static_cast<int>(polys.size()) > ind && ind >= 0);
}

bool Group::isVertexAt(int poly, int vert) {
    if (isPolygonAt(poly)) {
        if (getPolygon(poly)->isVertexAt(vert)) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Polygon> Group::getPolygon(int ind) {
    if (isPolygonAt(ind)) {
        return polys.at(ind);
    }
    return std::make_shared<Polygon>(Polygon("Empty Polygon"));
}

std::vector<std::shared_ptr<Polygon>> Group::getPolygons() {
    return polys;
}

std::vector<std::array<float, 2>> Group::getVertices() {
    std::vector<std::array<float, 2>> verts;
    for (unsigned int i = 0; i < polys.size(); i++) {
        for (unsigned int  j = 0; j < polys.at(i)->getVertices().size(); j++) {
            verts.push_back(polys.at(i)->getVertices().at(j));
        }
    }
    return verts;
}

void Group::addGroup(Group gr) {
    addPolygons(gr.getPolygons());
}

void Group::rotate(std::array<float, 2> pivot, float angle) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->rotate(pivot, angle);
    }
}

void Group::shift(float offset, int axis) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->shift(offset, axis);
    }
}

void Group::centerAt(float offset, int axis) {
    float max = getExtreme(true, axis);
    float min = getExtreme(false, axis);
    float center = ((max - min) / 2.0) + min;
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->shift(offset - center, axis);
    }
}

void Group::centerAt(std::array<float, 2> point) {
    centerAt(point.at(0), 0);
    centerAt(point.at(1), 1);
}

void Group::scale(float factor) {
    std::array<float, 2> center = getCenter();
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->scale(center, factor, 0);
        polys.at(i)->scale(center, factor, 1);
    }
}

float Group::getExtreme(bool tMaxfMin, int axis) {
    return GeometryInfo::getExtreme(getVertices(), tMaxfMin, axis);
}

std::array<float, 2> Group::getCenter() {
    return GeometryInfo::getCenter(getVertices());
}

void Group::setColor(std::array<float, 4> color) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->setColor(color);
    }
}

void Group::shiftColor(std::array<float, 4> shiftColor) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->shiftColor(shiftColor);
    }
}

void Group::shiftColorComponent(float shift, int component) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->shiftColorComponent(shift, component);
    }
}

void Group::shiftColorLightness(float shift) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i)->shiftColorLightness(shift);
    }
}

void Group::scatterColorComponent(float maxChange, int component) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        //(rand() / (float)RAND_MAX) results in 0.0 through 1.0
        polys.at(i)->shiftColorComponent((rand() / (float)RAND_MAX) * maxChange, component);
    }
}

void Group::scatterColorLightness(float maxChange) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        //(rand() / (float)RAND_MAX) results in 0.0 through 1.0,
        //Multiplying by two is 0.0 to 2.0,
        //Subtracting one is -1.0 to 1.0
        float randShift = (((rand() / (float)RAND_MAX) * 2) - 1) * maxChange;
        polys.at(i)->shiftColorLightness(randShift);
    }
}


std::vector<std::string> Group::getStatus() {
    std::vector<std::string> groupStatus;
    groupStatus.push_back("[Group] " + name + ":");
    for (unsigned int i = 0; i < polys.size(); i++) {
        std::vector<std::string> polyStatus = polys.at(i)->getStatus(i);
        for (unsigned int j = 0; j < polyStatus.size(); j++) {
            groupStatus.push_back("\t" + polyStatus.at(j));
        }
    }
    return groupStatus;
}

bool Group::saveGroup() {
    std::ofstream saveStream;
    saveStream.open("./saves/" + Group::name + ".txt");
    if (saveStream.is_open()) {
        saveStream << strVectToNewlines(getStatus());
        saveStream.close();
        return true;
    } else {
        return false;
    }
}

void Group::loadGroup() {

}

std::string Group::strVectToNewlines(std::vector<std::string> vect) {
    std::string str;
    for (unsigned int i = 0; i < vect.size(); i++) {
        str.append(vect.at(i) + "\n");
    }
    return str;
}