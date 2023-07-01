#include "DrawGroup.h"

//Constructor
DrawGroup::DrawGroup(std::string name, float whratio, SDL_Window *window, std::shared_ptr<SDL_GLContext> ctx, GLint color, GLint transparency) : Group(name) {
    DrawGroup::whratio = whratio;
    DrawGroup::window = window;
    DrawGroup::ctx = ctx;
    DrawGroup::color = color;
    DrawGroup::transparency = transparency;
}

void DrawGroup::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawGroup::draw() {
    //Need a context, window, shader program, and some polygons to draw anything
    if ((ctx != nullptr) && (window != nullptr) && (polys.size() > 0)) {

        //For as many polygons as are in the group...
        for (int i = 0; i < static_cast<int>(polys.size()); i++) {
            std::shared_ptr<Polygon> poly = getPolygon(i);
            std::vector<std::array<float, 2>> verts;

            //Collect and modify values
            for (int j = 0; j < static_cast<int>(poly->getVertices().size()); j++) {
                verts.push_back(std::array<float, 2>{
                    (poly->getVertices().at(j)[0] + panX),            //x
                    ((poly->getVertices().at(j)[1] + panY) * whratio)   //y
                });
            }

            //Set buffer data
            glBufferData(GL_ARRAY_BUFFER, verts.size() * 2 * sizeof(verts[0][0]), verts.data(), GL_DYNAMIC_DRAW);

            //Set colors
            float r = poly->getColor()[0];
            float g = poly->getColor()[1];
            float b = poly->getColor()[2];
            float t = poly->getColor()[3];
            glUniform3f(color, r, g, b);
            glUniform1f(transparency, t);
            
            glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());
        }
        
        SDL_GL_SwapWindow(window);
    }
}

float DrawGroup::getPan(int axis) {
    if (axis == 0) {
        return panX;
    } else if (axis == 1) {
        return panY;
    }
    return 0.0;
}

std::array<float, 2> DrawGroup::getPan() {
    return {panX, panY};
}

void DrawGroup::setPan(std::array<float, 2> pan) {
    panX = std::get<0>(pan);
    panX = std::get<1>(pan);
}

void DrawGroup::setPan(float pan, int axis) {
    if (axis == 0) {
        panX = pan;
    } else if (axis == 1) {
        panY = pan;
    }
}