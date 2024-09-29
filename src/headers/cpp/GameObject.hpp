#ifndef ObjectHPP
#define ObjectHPP
#include <string>
#include <vector>
#include "RevenantVectors.h"
#include "RevenantMesh.hpp"
struct Transform {
    Vector3 position, rotation, scale;
    Transform(Vector3 position, Vector3 rotation, Vector3 scale);

    void SetScale(Vector3 scale);
    void MultiplyScale(Vector3 factor);

    void SetRotationDegrees(Vector3 rotation);
    void SetRotationRadians(Vector3 rotation);
    void RotateByDegrees(Vector3 theta);
    void RotateByRadians(Vector3 theta);

    void SetPosition(Vector3 position);
    void Translate(Vector3 translation);
};
class GameObject {
    std::string name;
    Vector3 transform;
    GameObject* children;
    bool isStatic;
    void Start();
    void OnEachFrame();
};

#endif