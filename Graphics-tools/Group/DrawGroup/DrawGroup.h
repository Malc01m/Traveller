#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <array>

#include "../Group/Group.h"

class DrawGroup : public Group {

    public:

        DrawGroup(std::string name, float whratio, SDL_Window *window, std::shared_ptr<SDL_GLContext> ctx, GLint color, GLint transparency);
        
        //Clears the screen
        void clear();

        //Draws the contents of the group to screen
        void draw();

        //Returns the distance the image is panned on an axis
        float getPan(int axis);
        //Returns the distance the image is panned on both axes
        std::array<float, 2> getPan();

        //Sets the distance the image is panned on an axis
        void setPan(float pan, int axis);
        //Sets the distance the image is panned on both axes
        void setPan(std::array<float, 2> pan);

    private:

        GLint color = 0;
        GLint transparency = 0;

        float whratio;

        SDL_Window *window = nullptr;
        std::shared_ptr<SDL_GLContext> ctx = nullptr;

        float panX = 0.0;
        float panY = 0.0;

};