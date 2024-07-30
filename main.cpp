#include <ctime>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Integrators/sdlglSetup.h"
#include "Integrators/glewSetup.cpp"

#include "Graphics-tools/Shader/ShaderProgram.h"
#include "Graphics-tools/Shader/source.cpp"

#include "Graphics-tools/Group/Group/Group.h"
#include "Graphics-tools/Group/DrawGroup/DrawGroup.h"
#include "Graphics-tools/Group/EditGroup/EditGroup.h"
#include "Graphics-tools/Group/GridGroup/GridGroup.h"

#include "Math-tools/Geometry/Polygon/Polygon.h"
#include "Math-tools/Geometry/GeometryGen/GeometryGen.h"
#include "Math-tools/Geometry/GeometryInfo/GeometryInfo.h"
#include "Math-tools/Color/ColorMutators/ColorMutators.h"

#include "World-tools/World/World.h"

using namespace GeometryInfo;
using namespace GeometryGen;
using namespace ColorMutators;

int main () {

    // Seed rand with the current time
    std::srand(std::time(nullptr));

    // Initialize needed libraries
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

    std::cout << "Traveller v0.0\n";

    // Initialize test editor
    EditGroup eg("EditGroup", whratio, window, ctx, color, transparency);

    std::string test = "World";
    if (test == "grid") {

        // Make grid
        GridGroup gg("Grid Group", 0.06, 0.06, (M_PI / 7), (M_PI * 6 / 7));
        Polygon tile = regularPoly(4, 0.027);
        scale(tile, getCenter(tile), 2.1, 0);
        gg.fill(tile, 0, 0, 9, 9);
        centerAt(gg, {0, 0});

        eg.addGroup(gg);

        // Make things colorful to visually distinguish polygons
        scatterColorsComponent(eg, -0.4, COLOR_DATA_R);
        scatterColorsComponent(eg, -0.4, COLOR_DATA_G);
        scatterColorsComponent(eg, -0.4, COLOR_DATA_B);

    } else if (test == "trifield") {

        Group triField = triFieldRadial(2, 3, 0.2, 0, 0, 1.2);
        eg.addGroup(triField);

        // Make things colorful to visually distinguish polygons
        scatterColorsComponent(eg, -0.4, COLOR_DATA_R);
        scatterColorsComponent(eg, -0.4, COLOR_DATA_G);
        scatterColorsComponent(eg, -0.4, COLOR_DATA_B);

    } else if (test == "World") {

        std::cout << "Launching world test...\n";
        World world = World();
        std::cout << "World created\n";
        eg.addGroup(world.getWorldGroup());

    }

    eg.initEditor();
}