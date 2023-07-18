#ifndef UIGROUP_H
#define UIGROUP_H

#include <functional>

#include "Group.h"

class UIGroup : public Group {
    public: 
        /**
         * @brief Adds a polygon pointer to the group
         * 
         * @param poly The polygon pointer to be added
         * @param func The function to associate with poly
         */
        void addPolygon(std::shared_ptr<Polygon> poly, std::function<void()> func);

        /**
         * @brief Creates and adds a new polygon pointer to the group
         * 
         * @param poly The polygon pointer to be added
         * @param func The function to associate with poly
         */
        void addPolygon(Polygon poly, std::function<void()> func);

        /**
         * @brief Adds multiple object pointers to the group
         * 
         * @param polys The polygon pointers to be added
         * @param funcs The functions to associate with polys
         */
        void addPolygons(std::vector<std::shared_ptr<Polygon>> polys, 
                         std::vector<std::function<void()>> funcs);

        /**
         * @brief Removes all instances of a polygon pointer from the group
         * 
         * @param poly The object pointer to be removed
         * @attention Overrides Group's removePolygon
         */
        void removePolygon(std::shared_ptr<Polygon> poly);

        /**
         * @brief Calls the function of the first clickable containing the
         * given point
         * 
         * @param x The x position of the click
         * @param y The y position of the click
         */
        void handleClick(float x, float y);

    private:
        //A vector pairing indices of Group's polys to functions to be called
        //when they are clicked
        std::vector<std::tuple<int, std::function<void()>>> clickable;
};

#endif