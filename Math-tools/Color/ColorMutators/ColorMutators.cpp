#include "ColorMutators.h"
#include "Rand.h"

Color ColorMutators::shiftColorComponent(Color color, float shift, int component) {
    color.at(component) += shift;
    return color;
}

void ColorMutators::shiftColorsComponent(ColorsPtr colors, float shift, int component) {
    for (unsigned int i = 0; i < colors->size(); i++) {
        Color thisColor = *colors->at(i);
        thisColor = shiftColorComponent(thisColor, shift, component);
        ColorPtr thisColorPtr = std::make_shared<Color>(thisColor);
        colors->at(i) = thisColorPtr;
    }
}

Color ColorMutators::shiftColorLightness(Color color, float shift) {
    color.at(COLOR_DATA_R) += shift;
    color.at(COLOR_DATA_G) += shift;
    color.at(COLOR_DATA_B) += shift;
    return color;
}

void ColorMutators::shiftColorsLightness(ColorsPtr colors, float shift) {
    for (unsigned int i = 0; i < colors->size(); i++) {
        Color thisColor = *colors->at(i);
        thisColor = shiftColorLightness(thisColor, shift);
        ColorPtr thisColorPtr = std::make_shared<Color>(thisColor);
        colors->at(i) = thisColorPtr;
    }
}

Color ColorMutators::scatterColorComponent(Color color, float maxChange, ColorArrIndex component) {
    float shift = Rand::randFloatBetween(-maxChange, maxChange);
    color = shiftColorComponent(color, shift, component);
    return color;
}

void ColorMutators::scatterColorsComponent(ColorsPtr colors, float maxChange, ColorArrIndex component) {
    for (unsigned int i = 0; i < colors->size(); i++) {
        ColorPtr thisColor = colors->at(i);
        *thisColor = scatterColorComponent(*thisColor, maxChange, component);
    }
}

Color ColorMutators::scatterColorLightness(Color color, float maxChange) {
    float shift = Rand::randFloatBetween(-maxChange, maxChange);
    color = shiftColorLightness(color, shift);
    return color;
}

void ColorMutators::scatterColorsLightness(ColorsPtr colors, float maxChange) {
    for (unsigned int i = 0; i < colors->size(); i++) {
        ColorPtr thisColor = colors->at(i);
        *thisColor = scatterColorLightness(*thisColor, maxChange);
    }
}