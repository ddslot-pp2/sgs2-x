#include "vector4.h"

vector4::vector4()
{
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
    W = 1.0f;
}

vector4::vector4(float x, float y, float z, float w)
{
    X = x;
    Y = y;
    Z = z;
    W = w;
}
