#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <array>

#include "Group.h"

class DrawGroup : public Group {

    public:

        DrawGroup(std::string name, float whratio, SDL_Window *window, std::shared_ptr<SDL_GLContext> ctx, GLint color);
        
        /**
         * @brief Clears the screen
        */
        void clear();

        /**
         * @brief Draws the contents of the group to screen
        */
        void draw();

    private:

        GLint color = 0;
        GLint transparency = 0;

        float whratio;

        SDL_Window *window = nullptr;
        std::shared_ptr<SDL_GLContext> ctx = nullptr;

        /* Vectors are guaranteed to be contigious past C++98,
        so we can speed up rendering by putting all of our vertices 
        in here and accessing it as a c-style array. */
        std::vector<float> vba;

        /* Track poly location in vba by adding its index in the vba
        at the same index as it is located at in polys here. */
        std::vector<int> polyMap;

};

#endif