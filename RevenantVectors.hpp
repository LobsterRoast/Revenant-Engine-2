#ifndef RevenantVectors
#define RevenantVectors

class Vector3 {
    public:
        float x;
        float y;
        float z;
        Vector3();
        Vector3(float x, float y, float z);
};
Vector3 Normalize(Vector3 inputVector);
Vector3 CrossProduct(Vector3 a, Vector3 b);
float DotProduct(Vector3 a, Vector3 b);

#endif