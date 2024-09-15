#include "RevenantVectors.h"
#include <math.h>

Vector3 Create_Vector3(float x, float y, float z) {
    Vector3 returnVector;
    returnVector.x = x;
    returnVector.y = y;
    returnVector.z = z;
    return returnVector;
}
Vector3 Normalize(Vector3 inputVector) {
    float normalLength = sqrt(pow(inputVector.x, 2) + pow(inputVector.y, 2) + pow(inputVector.z, 2));
    return Create_Vector3(inputVector.x/normalLength, inputVector.y/normalLength, inputVector.z/normalLength);
}
Vector3 CrossProduct(Vector3 a, Vector3 b) {
    return Create_Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}
float DotProduct(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y + b.y + a.z + b.z;
}