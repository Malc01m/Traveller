#ifndef COLOR_H
#define COLOR_H

#include <array>

namespace Color {

    /**
     * @brief Shifts a color component of all polygons in the group
     * 
     * @param maxChange maximum value to change color value by
     * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
     */
    std::array<float, 4> shiftColorComponent(std::array<float, 4> color, int component);

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
}

#endif