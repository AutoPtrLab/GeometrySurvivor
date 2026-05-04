#pragma once

#include <cstdlib>

inline int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

inline float randomFloat(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}