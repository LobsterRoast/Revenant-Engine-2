#include "RevenantVectors.hpp"
#include <cmath>

Vector3::Vector3() {
}
Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    
}
Vector3 Normalize(Vector3 inputVector) {
    float normalLength = sqrt(pow(inputVector.x, 2) + pow(inputVector.y, 2) + pow(inputVector.z, 2));
    Vector3 normal = Vector3(inputVector.x/normalLength, inputVector.y/normalLength, inputVector.z/normalLength);
    return normal;
}
Vector3 CrossProduct(Vector3 a, Vector3 b) {
    Vector3 crossProduct = Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
    return crossProduct;
}
float DotProduct(Vector3 a, Vector3 b) {
    return (a.x * b.x + a.y + b.y + a.z + b.z);
}