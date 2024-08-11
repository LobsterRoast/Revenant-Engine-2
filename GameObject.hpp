#ifndef ObjectHPP
#define ObjectHPP
#include <string>
#include "RevenantVectors.hpp"
#include "RevenantMesh.hpp"

class GameObject {
    std::string name;
    Mesh* objMesh;
    Vector3 transform;
    void Start();
    void OnEachFrame();
};

#endif