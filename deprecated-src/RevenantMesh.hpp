#ifndef RevenantMesh
#define RevenantMesh
#include <string>
#include <vector>
#include "RevenantTris.h"
#include "RevenantVectors.h"

class Mesh {
    public:
        Vector3* vertices;
        Vector3* triangleIndices; // As the Tri class holds Vector3 pointers rather than objects, this variable will hold the indices of the vertices that each triangle points to.
        Tri* triangles;
        Mesh(std::string meshName);
        std::string currentLineData;
};
Mesh Create_Mesh(const unsigned char meshName[]);
#endif