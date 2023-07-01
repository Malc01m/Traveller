#include <tuple>

#include "../Group/Group.h"

class GridGroup : public Group {

    public:

        /**
         * @brief Creates a new GridGroup, a type of Group that manages Polygons
         *        in a new linear coordinate system. This constructor uses 
         *        default spacing and angles.
         */
        GridGroup();

        /**
         * @brief Creates a new GridGroup, a type of Group that manages Polygons
         *        in a new linear coordinate system.
         * 
         * @param xSpacing Screen space between x positions defined to be one 
         *                 unit away from each other
         * @param ySpacing Screen space between y positions defined to be one 
         *                 unit away from each other
         * @param xAxisAng Angle between the new x axis and the screen's x axis
         * @param yAxisAng Angle between the new y axis and the screen's y axis
         */
        GridGroup(float xSpacing, float ySpacing, float xAxisAng, float yAxisAng);

        /**
         * @brief Creates a new GridGroup, a type of Group that manages Polygons
         *        in a new linear coordinate system.
         * 
         * @param name The name of the group
         * @param xSpacing Screen space between x positions defined to be one 
         *                 unit away from each other
         * @param ySpacing Screen space between y positions defined to be one 
         *                 unit away from each other
         * @param xAxisAng Angle between the new x axis and the screen's x axis
         * @param yAxisAng Angle between the new y axis and the screen's y axis
         */
        GridGroup(std::string name, float xSpacing, float ySpacing, float xAxisAng, float yAxisAng);

        /**
         * @brief Fills the specified region with new Polygon references
         * 
         * @param poly The Polygon to make new references to and place in the grid
         * @param startx The x position to place the first new Polygon row at
         * @param starty The y position to place the first new Polygon column at
         * @param endx The x position to place the last new Polygon row at
         * @param endy The y position to place the last new Polygon column at
         */
        void fill(Polygon poly, int startx, int starty, int endx, int endy);

        void addPolygon(Polygon poly, int x, int y);

        /**
         * @brief Adds an Polygon reference to the grid
         * 
         * @param poly The Polygon reference to be added
         * @param x The x position to place poly at
         * @param y The y position to place poly at
         */
        void addPolygon(std::shared_ptr<Polygon> poly, int x, int y);

        /**
         * @brief Centers a referenced Polygon at the specified position on the 
         *        grid (but does not add it to the grid.)
         * 
         * @param x The x position to center poly at
         * @param y The y position to center poly at
         */
        void align(std::shared_ptr<Polygon> poly, float x, float y);

        /**
         * @brief Centers all Polygons in the grid at their coordinates, if they
         *        have been given any
         */
        void alignAll();

        /**
         * @brief Sets the screen space between x positions defined to be one 
         *        unit away from each other, and re-aligns all Polygons
         * 
         * @param xSpacing The new spacing between x positions
         */
        void setXSpacing(float xSpacing);

        /**
         * @brief Sets the screen space between y positions defined to be one 
         *        unit away from each other, and re-aligns all Polygons
         * 
         * @param ySpacing The new spacing between y positions
         */
        void setYSpacing(float ySpacing);

        void setXAxisAng(float xAxisAng);
        void setYAxisAng(float yAxisAng);

        /**
         * @brief Overides Group::shift so that the grid origin will be updated and align()
         * will continue to be correct relative to already-present polygons if moveOrigin is true
         * 
         * @param offset 
         * @param axis 
         * @param moveOrigin true if the origin of the grid alignment should be updated
         */
        void shift(float offset, int axis, bool moveOrigin);

    private:

        std::array<float, 2> origin = {0, 0};
        float xSpacing = 0.06;
        float ySpacing = 0.06;
        float xAxisAng = 0;
        float yAxisAng = M_PI / 2;
        //Coords is a vector containing the index of an Polygon in ptrs 
        //inherited from Group, and its grid x and y coordinates.
        std::vector<std::tuple<int, float, float>> coords;

};