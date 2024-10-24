#include "DrawGroup.h"

//Constructor
DrawGroup::DrawGroup(std::string name, float whratio, SDL_Window *window, std::shared_ptr<SDL_GLContext> ctx, GLint color) : Group(name) {
    DrawGroup::whratio = whratio;
    DrawGroup::window = window;
    DrawGroup::ctx = ctx;
    DrawGroup::color = color;
}

void DrawGroup::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawGroup::draw() {
    //Need a context, window, shader program, and some polygons to draw anything
    if ((ctx != nullptr) && (window != nullptr) && (polys->size() > 0)) {

        //For as many polygons as are in the group...
        for (int i = 0; i < static_cast<int>(polys->size()); i++) {
            std::shared_ptr<Polygon> poly = getPolygon(i);
            std::vector<std::array<float, 2>> verts;

            //Collect and modify values
            for (int j = 0; j < static_cast<int>(poly->getVertices()->size()); j++) {
                verts.push_back(std::array<float, 2>{
                    poly->getVertices()->at(j)->at(0),            //x
                    (poly->getVertices()->at(j)->at(1) * whratio)   //y
                });
            }

            //Set buffer data
            glBufferData(GL_ARRAY_BUFFER, verts.size() * 2 * sizeof(verts[0][0]), verts.data(), GL_DYNAMIC_DRAW);

            //Set colors
            glUniform4fv(color, 1, poly->getColor().data());
            
            glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());
        }
        
        SDL_GL_SwapWindow(window);
    }
}