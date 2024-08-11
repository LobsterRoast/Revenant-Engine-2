#include "RevenantTris.hpp"
#include "RevenantVectors.hpp"

Tri::Tri(Vector3* a, Vector3* b, Vector3* c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void Tri::SetNormal() {
    normal = CrossProduct(*a, *b);
}

float Deg2Rad(float thetaD) {
    return thetaD * ThetaConversionConstant;
}
float Rad2Deg(float thetaR) {
    return thetaR / ThetaConversionConstant;
}