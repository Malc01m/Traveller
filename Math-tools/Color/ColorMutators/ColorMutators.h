#ifndef COLORMUTATORS_H
#define COLORMUTATORS_H

#include <array>
#include <memory>
#include <vector>
#include <iostream>

using Color = std::array<float, 4>;
using ColorPtr = std::shared_ptr<Color>;
using ColorsPtr = std::shared_ptr<std::vector<std::shared_ptr<Color>>>;

enum ColorArrIndex {
    COLOR_DATA_R,
    COLOR_DATA_G,
    COLOR_DATA_B,
    COLOR_DATA_A
};

namespace ColorMutators {

    /**
     * @brief Shifts a color component of all polygons in the group
     * 
     * @param shift amount to shift component by
     * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
     */
    Color shiftColorComponent(Color color, float shift, int component);
    void shiftColorsComponent(ColorsPtr colors, float shift, int component);

    /**
     * @brief Shifts the lightnesses of the colors of all polygons in 
     * the group
     * 
     * @param maxChange maximum value to change color values by
     */
    Color shiftColorLightness(Color color, float shift);
    void shiftColorsLightness(ColorsPtr color, float shift);

    /**
     * @brief Scatters a color component of all polygons in the group
     * 
     * @param maxChange maximum value to change color value by
     * @param component 0 is red, 1 is green, 2 is blue, 3 is alpha
     */
    Color scatterColorComponent(Color color, float maxChange, ColorArrIndex component);
    void scatterColorsComponent(ColorsPtr colors, float maxChange, ColorArrIndex component);

    /**
     * @brief Scatters the lightnesses of the colors of all polygons in 
     * the group
     * 
     * @param maxChange maximum value to change color values by
     */
    Color scatterColorLightness(Color color, float maxChange);
    void scatterColorsLightness(ColorsPtr colors, float maxChange);
}

#endif