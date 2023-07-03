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

        /**
         * @brief Constructs a polyogn
         * 
         * @param name The name of the polygon
        */
        Polygon(std::string name);

        /**
         * @brief Constructs a polyogn
         * 
         * @param name The name of the polygon
         * @param vertices The vertices of the polygon
         * @param color The color of the polygon in (r, g, b, a) format
        */
        Polygon(std::string name, std::vector<std::array<float, 2>> vertices, std::array<float, 4> color);
        
        // Copy constructor
        Polygon(const Polygon &poly);

        // Typecasts
        operator std::vector<std::array<float, 2>>() {return vertices;};

        // Setters

        /**
         * @brief Sets the polygon's vertices
         * 
         * @param vertices Vertices to give the polygon
        */
        void setVertices(std::vector<std::array<float, 2>> vertices);

        /**
         * @brief Sets the polygon's color 
         * 
         * @param color The new color of the polygon in (r, g, b, a) format
        */
        void setColor(std::array<float, 4> color);

        /**
         * @brief Sets the polygon's name
         * 
         * @param name Name to give the polygon
        */
        void setName(std::string name);

        // Getters

        /** 
         * @brief Checks if there is a vertex at an index
         * 
         * @param ind The index in polygon's vertices to check for a vertex at
         * @returns true if the vertex exists
        */
        bool isVertexAt(int ind);

        /**
         * @brief Gets the polygon's vertices
         * 
         * @returns the polygon's vertices as a vector of floats in (x, y), (x, y)... format
        */
        std::vector<std::array<float, 2>> getVertices();

        /**
         * @brief Gets a vertex from the polygon's vertices
         * 
         * @param ind The index of the vertex to get
         * @returns The vertex at the given index in vertices
        */
        std::array<float, 2> getVertexAt(int ind);

        /** 
         * @returns Returns polygon's color as an array of floats in (r, g, b, t) format
        */
        std::array<float, 4> getColor();    

        // Manipulators

        /**
         * @brief Adds a vertex to the polygon
         * 
         * @param x The x coordinate of the new vertex
         * @param y The y coordinate of the new vertex
        */
        void addVertex(float x, float y);

        /**
         * @brief Adds a vertex to the polygon
         * 
         * @param vert The x, y coordinates of the new vertex
        */
        void addVertex(std::array<float, 2> vert);

        /**
         * @brief Removes a vertex
         * 
         * @param ind The index of the vertex to remove from vertices
        */
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

        /**
         * @brief 
        */
        float getMin(int axis);
        float getMax(int axis);
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