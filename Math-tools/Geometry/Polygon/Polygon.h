#ifndef POLYGON_H
#define POLYGON_H

#include <array>
#include <vector>
#include <tuple>
#include <math.h>
#include <string>

class Polygon {

    public:

        // Constructors
        Polygon(std::string name);
        Polygon(std::string name, std::vector<std::array<float, 2>> vertices, std::array<float, 4> color);
        
        // Copy constructor
        Polygon(const Polygon &poly);

        // Typecasts
        operator std::vector<std::array<float, 2>>() {return vertices;};

        // Setters

        // Sets the polygon's vertices to those in vector vs
        void setVertices(std::vector<std::array<float, 2>> vertices);

        // Sets the polygon's color to c, an array of floats in (r, g, b, t) format
        void setColor(std::array<float, 4> color);

        void setName(std::string name);

        // Getters

        /** 
         * @brief Returns true if a vertex exists at the given index
        */
        bool isVertexAt(int ind);

        // Returns the polygon's vertices as a vector of floats in (x, y), (x, y)... format
        std::vector<std::array<float, 2>> getVertices();

        std::array<float, 2> getVertexAt(int ind);

        // Returns polygon's color as an array of floats in (r, g, b, t) format
        std::array<float, 4> getColor();    

        // Manipulators

        // Adds a vertex (x, y) to the end of vertices
        void addVertex(float x, float y);
        void addVertex(std::array<float, 2> vert);

        // Removes the vertex at the given index
        bool removeVertex(int ind);

        /**
         * @brief Shifts the vertex at the given ind
         * 
         * @param axis
         * @param offset
         */
        bool shiftVertex(int ind, int axis, float offset);

        /**
         * @brief Shifts the color of the polygon by shiftColor
         * 
         * @param shiftColor The values to be added to color
         */
        void shiftColor(std::array<float, 4> shiftColor);

        /**
         * @brief Shifts a component of the color of the polygon by shift
         * 
         * @param shift The value to be added to a color component
         * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
         */
        void shiftColorComponent(float shift, int component);

        /**
         * @brief Shifts the lightness of the color of the polygon by shift
         * 
         * @param shift The amount of lightness to be added to color
         */
        void shiftColorLightness(float shift);

        //Transforms

        float getExtreme(bool tMaxfMin, int axis);
        std::array<float, 2> getCenter();
        void rotate(std::array<float, 2> pivot, float angle);
        void shift(float offset, int axis);
        void centerAt(float offset, int axis);
        void centerAt(std::array<float, 2> center);
        void scale(std::array<float, 2> center, float factor, int axis);

        //Debug

        std::vector<std::string> getStatus();
        std::vector<std::string> getStatus(int num);

    private:

        std::string name;

        //Polygon's vertices in (x, y), (x, y)... format
        std::vector<std::array<float, 2>> vertices;

        //Polygon's color in (r, g, b, t) format
        std::array<float, 4> color = {1.0, 1.0, 1.0, 1.0};

        // Status helper functions
        std::vector<std::string> getStatusVertices(std::vector<std::string>);
        std::vector<std::string> getStatusColor(std::vector<std::string>);

};

#endif