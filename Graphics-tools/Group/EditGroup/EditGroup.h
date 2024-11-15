#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <vector>
#include <array>

#include <SDL2/SDL.h>

#include "GeometryGen.h"
#include "GeometryInfo.h"
#include "Group.h"
#include "DrawGroup.h"

class EditGroup : public Group {

    public:

        EditGroup(std::string name, float whratio, SDL_Window *window, 
            std::shared_ptr<SDL_GLContext> ctx, GLint color);

        ///////////////////
        // Editor State //
        /////////////////
        
        /**
         * @brief Initializes the polygon group editor
         */
        void initEditor();

        ////////////////
        // Selection //
        //////////////

        /**
         * @brief Selects an Polygon by index
         * 
         * @param ind The index of the Polygon to be selected
         * @return false if the index is invalid
        */
        bool hoverPoly(int ind);

        /**
         * @brief Selects the next Polygon
         * 
         * @return false if the last Polygon is already selected
        */
        bool hoverNextPoly();

        /**
         * @brief Selects the previous Polygon
         * 
         * @return false if the first Polygon is already selected
        */
        bool hoverPrevPoly();

        /**
         * @brief Realigns the cursor with the currently hovered vertex
         * 
         * @return true if successfully realigned the cursor
         */
        bool hoverVertex();

        /**
         * @brief Hovers the cursor over a vertex
         * 
         * @param polyInd The index of the polygon for a vertex to be selected from
         * @param vertInd The index of the vertex to be selected
         * @return false if the index is invalid
        */
        bool hoverVertex(int polyInd, int vertInd);

        /**
         * @brief Hovers the cursor over the next vertex
         * 
         * @return false if the last vertex is already selected
        */
        bool hoverNextVertex();

        /**
         * @brief Hovers the cursor over the previous vertex
         * 
         * @return false if the first vertex is already selected
        */
        bool hoverPrevVertex();

        /////////////////////////////
        // Edit Selected Geometry //
        ///////////////////////////

        /**
         * @brief Moves the currently hovered-over vertex
         * 
         * @param axis The axis to move the vertex on
         * @param offset The distance to move the vertex
         * @return true if successfully moved a vertex
         */
        bool shiftHoveredVertex(int axis, float offset);

        ///////////////////
        // New geometry //
        /////////////////

        /**
         * @brief Creates a new regular polygon
         * 
         * @param verts Number of vertices
         * @param radius Distance from center to a vertex
         */
        void newRegPoly(int verts, float radius);

    private:

        // DrawGroup information (for DrawGroup construction in initEditor)
        GLint color = 0;
        float whratio;
        SDL_Window *window = nullptr;
        std::shared_ptr<SDL_GLContext> ctx = nullptr;
        
        // Modes
        int freeMoveMode = true;

        // Cursor

        // Position
        int polyHoverInd = 0;
        int vertHoverInd = 0;

        // Poly
        Polygon cursorPoly = GeometryGen::regularPoly(4, 0.01);
        std::shared_ptr<Polygon> vertCursor = 
            std::make_shared<Polygon>(cursorPoly);

};

#endif