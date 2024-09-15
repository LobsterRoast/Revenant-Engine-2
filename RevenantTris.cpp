#include "RevenantTris.h"
#include "RevenantVectors.h"

Tri Create_Tri(Vector3* a, Vector3* b, Vector3* c) {
    Tri returnTri;
    returnTri.a = a;
    returnTri.b = b;
    returnTri.c = c;
    return returnTri;
}

void SetNormal(Tri* tri) {
    tri->normal = CrossProduct(*tri->a, *tri->b);
}

float Deg2Rad(float thetaD) {
    return thetaD * ThetaConversionConstant;
}
float Rad2Deg(float thetaR) {
    return thetaR / ThetaConversionConstant;
}