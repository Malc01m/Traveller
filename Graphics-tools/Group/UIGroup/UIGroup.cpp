#include "./UIGroup.h"

void UIGroup::addPolygon(std::shared_ptr<Polygon> poly, std::function<void()> func) {
    polys.push_back(poly);
    clickable.push_back(std::make_tuple((int)(polys.size() - 1), func));
}

void UIGroup::addPolygon(Polygon poly, std::function<void()> func) {
    addPolygon(std::make_shared<Polygon>(poly), func);
}

void UIGroup::addPolygons(std::vector<std::shared_ptr<Polygon>> polys, 
                          std::vector<std::function<void()>> funcs) {
    
}

void UIGroup::removePolygon(std::shared_ptr<Polygon> poly) {

}

void UIGroup::handleClick(float x, float y) {

}
