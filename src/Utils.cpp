#include "Utils.h"

float screenToGLX(int x, int w) {
    return (float)x / w * 2.0f - 1.0f;
}

float screenToGLY(int y, int h) {
    return -((float)y / h * 2.0f - 1.0f);
}