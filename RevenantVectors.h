#ifndef RevenantVectors
#define RevenantVectors
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} HalfVector3;
Vector3 Create_Vector3(float x, float y, float z);
Vector3 Normalize(Vector3 inputVector);
Vector3 CrossProduct(Vector3 a, Vector3 b);
float DotProduct(Vector3 a, Vector3 b);

#ifdef __cplusplus
}
#endif

#endif