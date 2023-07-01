#pragma once

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
         * @brief Adds multiple object pointers to the group
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

        /** 
         * @brief Returns true if a polygon exists at the given index
        */
        bool isPolygonAt(int poly);

        /** 
         * @brief Returns true if a polygon exists at the given index
        */
        bool isVertexAt(int poly, int vert);

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

        //Group functions

        /**
         * @brief Adds all object pointers in another group to this group
         * 
         * @param gr The group to add object pointers from
         */
        void addGroup(Group gr);

        /**
         * @brief Rotates the contents of the group by angle around pivot
         * 
         * @param pivot pivot to rotate around
         * @param angle angle to rotate in radians
         */
        void rotate(std::array<float, 2> pivot, float angle);

        /**
         * @brief Shifts the entire group by offset on axis
         * 
         * @param offset the distance to shift by
         * @param axis the axis to shift along
         */
        void shift(float offset, int axis);

        /**
         * @brief Centers the contents of the group around the offset on axis
         * 
         * @param offset the location to center around
         * @param axis the axis to center on
         */
        void centerAt(float offset, int axis);

        /**
         * @brief Centers the contents of the group around point
         * 
         * @param point the point to center around
         */
        void centerAt(std::array<float, 2> point);

        /**
         * @brief Scales the contents of the group by factor
         * 
         * @param factor factor to scale by
         */
        void scale(float factor);

        /**
         * @brief Gets the lowest or highest value on axis in the group
         * 
         * @param tMaxfMin True if searching for a maximum, false if a minimum
         * @param axis Axis to find an extreme value on
         * @return The extreme value
         */
        float getExtreme(bool tMaxfMin, int axis);

        /**
         * @brief Gets the central point of the contents of the group
         * 
         * @return std::array<float, 2> 
         */
        std::array<float, 2> getCenter();

        /**
         * @brief Sets the color of all polygons in the group to color
         * 
         * @param color to be applied to all polygons
         */
        void setColor(std::array<float, 4> color);

        /**
         * @brief Shifts the color of all polygons in the group by colorShift
         * 
         * @param shiftColor to be applied to all polygons
         */
        void shiftColor(std::array<float, 4> shiftColor);

        /**
         * @brief Shifts a color component of all polygons in the group
         * 
         * @param maxChange maximum value to change color value by
         * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
         */
        void shiftColorComponent(float shift, int component);

        /**
         * @brief Shifts the lightnesses of the colors of all polygons in 
         * the group
         * 
         * @param maxChange maximum value to change color values by
         */
        void shiftColorLightness(float shift);

        /**
         * @brief Scatters a color component of all polygons in the group
         * 
         * @param maxChange maximum value to change color value by
         * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
         */
        void scatterColorComponent(float maxChange, int component);

        /**
         * @brief Scatters the lightnesses of the colors of all polygons in 
         * the group
         * 
         * @param maxChange maximum value to change color values by
         */
        void scatterColorLightness(float maxChange);

        /**
         * @brief Returns a string containing a report about the polygons 
         * in the group for debug purposes
         * 
         * @return std::string A string representing the polygon contents 
         * of group
         */
        std::vector<std::string> getStatus();

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

        /**
         * TODO: Move out of group
         * @brief Converts a vector of strings to a string with newlines
         * 
         * @param arr 
         * @return std::string 
         */
        std::string strVectToNewlines(std::vector<std::string> vect);

};