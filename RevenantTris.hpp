#ifndef RevenantTris
#define RevenantTris
#include "RevenantVectors.hpp"

class Tri {
    public:
        Vector3* a;
        Vector3* b;
        Vector3* c;
        Vector3 normal;
        Tri(Vector3* a, Vector3* b, Vector3* c, Vector3 normal);
        Tri(Vector3* a, Vector3* b, Vector3* c);
};
const float ThetaConversionConstant = 3.14159/180;
float Deg2Rad(float thetaD);
float Rad2Deg(float thetaR);

#endif