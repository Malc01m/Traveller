#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <memory>
#include <string>

#include "Polygon.h"

class Group {

    public:

        //Constructors
        
        Group();
        Group(Polygon poly);
        Group(std::string name);
        Group(std::string name, Polygon poly);
        Group(std::string name, std::vector<std::shared_ptr<Polygon>> polys);
        Group(std::vector<std::shared_ptr<Polygon>> polys);

        //Object functions

        /**
         * @brief Sets the name of the group
         * 
         * @param name new name of the group
         */
        void setName(std::string name);

        ///////////////////
        // Set geometry //
        /////////////////

        /**
         * @brief Adds a polygon pointer to the group
         * 
         * @param poly The polygon pointer to be added
         */
        void addPolygon(std::shared_ptr<Polygon> poly);

        /**
         * @brief Creates and adds a new polygon pointer to the group
         * 
         * @param poly The polygon pointer to be added
         */
        void addPolygon(Polygon poly);

        /**
         * @brief Creates pointers to and adds polygons to the group
         * 
         * @param polys vector of Polygons to be pointerized and added
        */
        void addPolygons(std::vector<Polygon> polys);

        /**
         * @brief Adds multiple polygon pointers to the group
         * 
         * @param polys The polygon pointers to be added
         */
        void addPolygons(std::vector<std::shared_ptr<Polygon>> polys);

        /**
         * @brief Removes all instances of a polygon pointer from the group
         * 
         * @param poly The object pointer to be removed
         */
        void removePolygon(std::shared_ptr<Polygon> poly);

        /**
         * @brief Removes all polygon pointers from the group
         */
        void empty();

        /**
         * @brief Replaces all polygon pointers in the group
         * 
         * @param polys The polygon pointers that the group's previous polygon
         *              pointers will be replaced by
         */
        void setPolygons(std::vector<std::shared_ptr<Polygon>> polys);

        /**
         * @brief Replaces all polygons in the group
         * 
         * @param polys The polygons that the group's previous polygon
         *              pointers will be replaced by
         */
        void setPolygons(std::vector<Polygon> polys);

        ////////////////
        // Set color //
        //////////////

        /**
         * @brief Sets the color of the polygon at the given index
         * 
         * @param color Color to be applied
         */
        void setColor(int polyIndx, std::array<float, 4> color);

        /**
         * @brief Sets the colors polygons in the group to same-index colors
         * 
         * @param colors vector of colors to replace current colors
         */
        void setColors(std::vector<std::array<float, 4>> colors);

        ///////////////////
        // Get Geometry //
        /////////////////

        /** 
         * @brief Returns true if a polygon exists at the given index
        */
        bool isPolygonAt(int poly);

        /** 
         * @brief Returns true if a polygon exists at the given index
        */
        bool isVertexAt(int poly, int vert);

        /**
         * @returns The number of polygons in the group
        */
        int getNumPolygons();

        /**
         * @brief Returns a pointer to a polygon in the group, or an empty
         * polygon if none exists at the given index
         */
        std::shared_ptr<Polygon> getPolygon(int poly);

        /**
         * @brief Returns pointers to all polygons in the group
         */
        std::vector<std::shared_ptr<Polygon>> getPolygons();

        /**
         * @brief Returns all vertices in all polygons in the group
         */
        std::vector<std::array<float, 2>> getVertices();

        ///////////////////////
        // Group Operations //
        /////////////////////

        /**
         * @brief Adds all object pointers in another group to this group
         * 
         * @param gr The group to add object pointers from
         */
        void addGroup(Group gr);

        /////////////
        // Status //
        ///////////

        /**
         * @brief Returns a string containing a report about the polygons 
         * in the group for debug purposes
         * 
         * @return std::string A string representing the polygon contents 
         * of group
         */
        std::vector<std::string> getStatus();

        /**
         * @brief Prints the group's status report to console
        */
        void printStatus();

        /////////////////////////
        // Saving and loading //
        ///////////////////////

        /**
         * @brief Saves getStatus() to a file in a generated saves subdirectory
         * 
         * @returns true on successful write
         */
        bool saveGroup();

        /**
         * TODO: Implement
         * @brief Loads group information from a file into this group
         */
        void loadGroup();

    protected:

        std::string name = "Unnamed_group";
        std::vector<std::shared_ptr<Polygon>> polys;
        // Indices of vertices that are part of a joint group.
        // (joint number, poly, vert)
        std::vector<std::array<int, 3>> joints;

        /**
         * TODO: Move out of group
         * @brief Converts a vector of strings to a string with newlines
         * 
         * @param arr 
         * @return std::string 
         */
        std::string strVectToNewlines(std::vector<std::string> vect);

};

#endif