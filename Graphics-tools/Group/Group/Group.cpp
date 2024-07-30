#include <fstream>
#include <iostream>

#include "Group.h"
#include "Rand.h"
#include "StringTools.h"

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

Group::Group(std::string name, PolysPtr polys) {
    Group::name = name;
    Group::polys = polys;
}

Group::Group(PolysPtr polys) {
    Group::polys = polys;
}

void Group::setName(std::string name) {
    Group::name = name;
}

void Group::addPolygon(std::shared_ptr<Polygon> poly) {
    polys->push_back(poly);
}

void Group::addPolygon(Polygon poly) {
    poly.decoupleVerts();
    poly.decoupleColor();
    polys->push_back(std::make_shared<Polygon>(poly));
}

void Group::addPolygons(std::vector<Polygon> polys) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        polys.at(i).decoupleVerts();
        polys.at(i).decoupleColor();
        Group::polys->push_back(std::make_shared<Polygon>(polys.at(i)));
    }
}

void Group::addPolygons(std::vector<std::shared_ptr<Polygon>> polys) {
    for (unsigned int i = 0; i < polys.size(); i++) {
        Group::polys->push_back(polys.at(i));
    }
}

void Group::removePolygon(std::shared_ptr<Polygon> poly) {
    for (unsigned int i = 0; i < polys->size(); i++) {
        if (polys->at(i).get() == poly.get()) {
            polys->erase(polys->begin() + i);
        }
    }
}

void Group::empty() {
    if (polys->size() > 0) {
        polys = PolysPtr();
    }
}

void Group::setPolygons(PolysPtr polys) {
    Group::polys = polys;
}

void Group::setPolygons(std::vector<Polygon> polys) {
    std::vector<std::shared_ptr<Polygon>> polyPtrs;
    for (unsigned int i = 0; i < polys.size(); i++) {
        polyPtrs.push_back(std::make_shared<Polygon>(polys.at(i)));
    }
    Group::polys = std::make_shared<std::vector<std::shared_ptr<Polygon>>>(polyPtrs);
}

bool Group::isPolygonAt(int ind) {
    return (static_cast<int>(polys->size()) > ind && ind >= 0);
}

bool Group::isVertexAt(int poly, int vert) {
    if (isPolygonAt(poly)) {
        if (getPolygon(poly)->isVertexAt(vert)) {
            return true;
        }
    }
    return false;
}

int Group::getNumPolygons() {
    return polys->size();
}

std::shared_ptr<Polygon> Group::getPolygon(int ind) {
    if (isPolygonAt(ind)) {
        return polys->at(ind);
    }
    return std::make_shared<Polygon>(Polygon("Empty Polygon"));
}

PolysPtr Group::getPolygons() {
    return polys;
}

std::vector<std::array<float, 2>> Group::getVertices() {
    std::vector<std::array<float, 2>> verts;
    for (unsigned int i = 0; i < polys->size(); i++) {
        for (unsigned int  j = 0; j < polys->at(i)->getVertices()->size(); j++) {
            verts.push_back(*polys->at(i)->getVertices()->at(j));
        }
    }
    return verts;
}

void Group::addGroup(Group gr) {
    addPolygons(*gr.getPolygons());
}

void Group::setColor( int polyIndx, std::array<float, 4> color) {
    // TODO Check bounds
    polys->at(polyIndx)->setColor(color);
}

void Group::setColors(std::array<float, 4> color) {
    // TODO Check bounds, for to while
    for (unsigned int i = 0; i < polys->size(); i++) {
        polys->at(i)->setColor(color);
    }
}

void Group::setColors(std::vector<std::array<float, 4>> colors) {
    // TODO Check bounds, for to while
    for (unsigned int i = 0; i < polys->size(); i++) {
        polys->at(i)->setColor(colors.at(i));
    }
}

std::vector<std::string> Group::getStatus() {
    std::vector<std::string> groupStatus;
    groupStatus.push_back("[Group] " + name + ":");
    for (unsigned int i = 0; i < polys->size(); i++) {
        std::vector<std::string> polyStatus = polys->at(i)->getStatus(i);
        for (unsigned int j = 0; j < polyStatus.size(); j++) {
            groupStatus.push_back("\t" + polyStatus.at(j));
        }
    }
    return groupStatus;
}

void Group::printStatus() {
    std::vector<std::string> groupStat = getStatus();
    for (unsigned int i = 0; i < groupStat.size(); i++) {
        std::cout << groupStat.at(i) << '\n';
    }
}

bool Group::saveGroup() {
    std::ofstream saveStream;
    saveStream.open("./saves/" + Group::name + ".txt");
    if (saveStream.is_open()) {
        saveStream << StringTools::strVectToNewlines(getStatus());
        saveStream.close();
        return true;
    } else {
        return false;
    }
}

void Group::loadGroup() {

}