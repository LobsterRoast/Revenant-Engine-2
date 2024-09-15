#ifndef RevenantMesh
#define RevenantMesh
#include <string>
#include <vector>
#include "RevenantTris.h"
#include "RevenantVectors.h"

typedef struct {
    HalfVector3 vertices[1024];
    Vector3 triangleIndices[4096]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    unsigned char currentLineData[];
} LowDtlMesh;

typedef struct {
    HalfVector3 vertices[32768];
    Vector3 triangleIndices[131072]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    unsigned char currentLineData[];
} MedDtlMesh;

typedef struct {
    HalfVector3 vertices[2097152];
    Vector3 triangleIndices[2097152]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    unsigned char currentLineData[];
} HighDtlMesh ;



typedef struct {
} CL_Mesh
Mesh Create_Mesh(const unsigned char meshName[]);
#endif