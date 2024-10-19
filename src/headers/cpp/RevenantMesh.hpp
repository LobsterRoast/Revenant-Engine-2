#ifndef RevenantMesh
#define RevenantMesh
#include <string>
#include <vector>
#include "RevenantTris.h"
#include "RevenantVectors.h"
#include "clHeap.hpp"

typedef struct {
    Vector3 vertices[1024];
    Tri triangles[4096]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    char name[20];
} LowDtlMesh;

typedef struct {
    Vector3 vertices[32768];
    Tri triangles[131072]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    char name[20];
} MedDtlMesh;

typedef struct {
    Vector3 vertices[2097152];
    Tri triangles[2097152]; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
    unsigned short triCount;
    unsigned short vertexCount;
    char name[20];
} HighDtlMesh;

LowDtlMesh Create_LowDtlMesh(std::string meshName);
MedDtlMesh Create_MedDtlMesh(std::string meshName);
HighDtlMesh Create_HighDtlMesh(std::string meshName);
#endif