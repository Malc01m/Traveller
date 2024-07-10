#include <math.h>

#include "Rand.h"

float Rand::randFloatBetween(float min, float max) {
    return (rand() / (RAND_MAX / (max - min))) + min;
}

int Rand::randIntBetween(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int Rand::randMultiple(int base, int minFactor, int maxFactor) {
    return base * Rand::randIntBetween(minFactor, maxFactor);
}