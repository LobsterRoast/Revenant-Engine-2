#ifndef RevenantTris
#define RevenantTris
#include "RevenantVectors.h"

typedef struct {
    Vector3* a;
    Vector3* b;
    Vector3* c;
    Vector3 normal;
} Tri;
Tri Create_Tri(Vector3* a, Vector3* b, Vector3* c);
void SetNormal(Tri* tri);
const float ThetaConversionConstant = 3.14159/180;
float Deg2Rad(float thetaD);
float Rad2Deg(float thetaR);

#endif