#ifndef REVENANT_TRIS_H
#define REVENANT_TRIS_H
#include "RevenantVectors.h"

typedef struct {
    unsigned short vertex[3];
    Vector3 normal;
} Tri;
Tri Create_Tri(unsigned short a, unsigned short b, unsigned short c);
extern const float ThetaConversionConstant;
float Deg2Rad(float thetaD);
float Rad2Deg(float thetaR);

#endif