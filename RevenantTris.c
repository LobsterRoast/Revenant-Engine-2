#include "RevenantTris.h"
#include "RevenantVectors.h"

Tri Create_Tri(unsigned short a, unsigned short b, unsigned short c) {
    Tri returnTri;
    returnTri.vertex[0] = a;
    returnTri.vertex[1] = b;
    returnTri.vertex[2] = c;
    return returnTri;
}

const float ThetaConversionConstant = 3.14159/180;
float Deg2Rad(float thetaD) {
    return thetaD * ThetaConversionConstant;
}
float Rad2Deg(float thetaR) {
    return thetaR / ThetaConversionConstant;
}