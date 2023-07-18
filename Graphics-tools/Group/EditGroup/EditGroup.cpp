#include <SDL2/SDL.h>

#include <iostream>

#include "EditGroup.h"
#include "GeometryInfo.h"

EditGroup::EditGroup(std::string name, std::shared_ptr<DrawGroup> drawGroupPtr) : Group(name) {
    EditGroup::drawGroupPtr = drawGroupPtr;
    vertCursor->setColor({1.0, 0.0, 0.0, 1.0});
    vertCursor->setName("Vertex cursor");
}

bool EditGroup::hoverPoly(int ind) {
    if ((ind >= 0) && (ind < static_cast<int>(polys.size()))) {
        polyHoverInd = ind;
        vertHoverInd = 0;
        hoverVertex(polyHoverInd, vertHoverInd);
        return true;
    }
    return false;
}

bool EditGroup::hoverNextPoly() {
    if (hoverPoly(polyHoverInd + 1)) {
        return true;
    }
    return false;
}

bool EditGroup::hoverPrevPoly() {
    if (hoverPoly(polyHoverInd - 1)) {
        return true;
    }
    return false;
}

void EditGroup::newRegPoly(int verts, float radius) {
    std::shared_ptr<Polygon> newRegPoly = std::make_shared<Polygon>(GeometryGen::regularPoly(verts, radius));
    newRegPoly->centerAt(cursorPoly.getCenter());
    polys.push_back(newRegPoly);
}

bool EditGroup::hoverVertex() {
    if (isVertexAt(polyHoverInd, vertHoverInd)) {
        std::array<float, 2> vertex = polys.at(polyHoverInd)->getVertexAt(vertHoverInd);
        vertCursor->centerAt(vertex);
        return true;
    }
    return false;
}

bool EditGroup::hoverVertex(int polyInd, int vertInd) {
    if (isVertexAt(polyInd, vertInd)) {
        polyHoverInd = polyInd;
        vertHoverInd = vertInd;
        hoverVertex();
        return true;
    }
    return false;
}

bool EditGroup::hoverNextVertex() {
    return hoverVertex(polyHoverInd, vertHoverInd + 1);
}

bool EditGroup::hoverPrevVertex() {
    return hoverVertex(polyHoverInd, vertHoverInd - 1);
}

bool EditGroup::shiftHoveredVertex(int axis, float offset) {
    if (isVertexAt(polyHoverInd, vertHoverInd)) {
        if (polys.at(polyHoverInd)->shiftVertex(vertHoverInd, axis, offset)) {
            hoverVertex();
            return true;
        }
    }
    return false;
}


void EditGroup::initEditor() {

    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    bool redrawFlag;

    if (polys.size() > 0) {
        hoverVertex(0, 0);
    }
    redraw();

    while (true) {

        redrawFlag = false;

        //Quit program
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) {

                if(!freeMoveMode) {
                    if (event.key.keysym.sym == SDLK_a) {
                        shiftHoveredVertex(0, -0.01);
                        redrawFlag = true;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        shiftHoveredVertex(1, -0.01);
                        redrawFlag = true;
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        shiftHoveredVertex(0, 0.01);
                        redrawFlag = true;
                    }
                    if (event.key.keysym.sym == SDLK_w) {
                        shiftHoveredVertex(1, 0.01);
                        redrawFlag = true;
                    }
                }

                //Cycle vertices
                if (event.key.keysym.sym == SDLK_q) {
                    hoverNextVertex();
                    redrawFlag = true;
                }
                if (event.key.keysym.sym == SDLK_e) {
                    hoverPrevVertex();
                    redrawFlag = true;
                }

                //Cycle polygons
                if (event.key.keysym.sym == SDLK_r) {
                    hoverNextPoly();
                    redrawFlag = true;
                }
                if (event.key.keysym.sym == SDLK_f) {
                    hoverPrevPoly();
                    redrawFlag = true;
                }

                //Mode toggles
                if (event.key.keysym.sym == SDLK_z) {
                    freeMoveMode = !freeMoveMode;
                }

            }
        }

        // Tests against states rather than events. Moves more continuously.
        if (freeMoveMode) {
            if (keyStates[SDL_SCANCODE_A]) {
                shiftHoveredVertex(0, -0.01);
                redrawFlag = true;
            }
            if (keyStates[SDL_SCANCODE_S]) {
                shiftHoveredVertex(1, -0.01);
                redrawFlag = true;
            }
            if (keyStates[SDL_SCANCODE_D]) {
                shiftHoveredVertex(0, 0.01);
                redrawFlag = true;
            }
            if (keyStates[SDL_SCANCODE_W]) {
                shiftHoveredVertex(1, 0.01);
                redrawFlag = true;
            }
        }

        //Quit editor
        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            break;
        }

        if (redrawFlag) {
            redraw();
            printStatus();
        }
    }
}

void EditGroup::redraw() {
    drawGroupPtr->empty();
    drawGroupPtr->addPolygons(polys);
    drawGroupPtr->addPolygon(vertCursor);
    drawGroupPtr->clear();
    drawGroupPtr->draw();
}