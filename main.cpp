#include <ctime>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "sdlglSetup.h"
#include "glewSetup.cpp"

#include "ShaderProgram.h"
#include "source.cpp"

#include "Group.h"
#include "DrawGroup.h"
#include "GridGroup.h"
#include "EditGroup.h"
#include "Polygon.h"
#include "World.h"
#include "GeometryGen.h"

int main () {

    std::srand(std::time(nullptr));

    sdlglSetup setup;
    if (!setup.setupFullscreen()) {
        return -1;
    }

    glewSetup gsetup;
    if (!gsetup.startGlew()) {
        SDL_Quit();
        return -1;
    }

    ShaderProgram sp;
    sp.add(Shader(shadersrc::vertsrc, GL_VERTEX_SHADER));
    sp.add(Shader(shadersrc::fragsrc, GL_FRAGMENT_SHADER));

    gsetup.enableTransparency();
    gsetup.setupGL(sp.compile());

    float whratio = setup.getScreenRatio();
    SDL_Window* window = setup.getWindow();
    std::shared_ptr<SDL_GLContext> ctx = setup.getGLContext();
    int color = gsetup.getColor();
    int transparency = gsetup.getTransparency();

    EditGroup eg("EditGroup", whratio, window, ctx, color, transparency);
    
    std::string test = "trifield";
    if (test == "grid") {

        // Make grid
        GridGroup gg("Grid Group", 0.06, 0.06, (M_PI / 7), (M_PI * 6 / 7));
        Polygon tile = GeometryGen::regularPoly(4, 0.027);
        tile.scale(tile.getCenter(), 2.1, 0);
        gg.fill(tile, 0, 0, 9, 9);
        gg.centerAt({0, 0});

        eg.addGroup(gg);

    } else if (test == "trifield") {

        Group triField = GeometryGen::triFieldRadial(2, 3, 0.2, 0, 0, 1.2);
        eg.addGroup(triField);
        eg.scatterColorComponent(-0.4, 0);
        eg.scatterColorComponent(-0.4, 1);
        eg.scatterColorComponent(-0.4, 2);

    } else if (test == "World") {

        World world = World();
        eg.addGroup(world.getWorldGroup());

    }

    eg.initEditor();

    /*
    SDL_Event event;
    while (true) {
        bool redraw = false;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Quit();
                    exit(0);
                }
                if (event.key.keysym.sym == SDLK_a) {
                    dg.scatterColorComponent(-0.1, 0);
                    redraw = true;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    dg.scatterColorComponent(-0.1, 1);
                    redraw = true;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    dg.scatterColorComponent(-0.1, 2);
                    redraw = true;
                }
                if (event.key.keysym.sym == SDLK_f) {
                    dg.scatterColorComponent(-0.1, 3);
                    redraw = true;
                }
            }
        }
        if (redraw) {
            dg.clear();
            dg.draw();
            dg.printStatus();
        }
    }
    */
}