#ifndef RAND_H
#define RAND_H

namespace Rand {
    float randFloatBetween(float min, float max);
    int randIntBetween(int min, int max);
    int randMultiple(int base, int minFactor, int maxFactor);
};

#endif