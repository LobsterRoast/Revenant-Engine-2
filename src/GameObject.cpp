#include "GameObject.hpp"
#include "RevenantTris.h"

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}
void Transform::SetScale(Vector3 scale) {
    this->scale = scale;
}
void Transform::MultiplyScale(Vector3 multiplicationFactors) {
    this->scale.x *= multiplicationFactors.x;
    this->scale.y *= multiplicationFactors.y;
    this->scale.z *= multiplicationFactors.z;
}
void Transform::SetRotationDegrees(Vector3 rotation) {
    this->rotation.x = Deg2Rad(rotation.x);
    this->rotation.y = Deg2Rad(rotation.y);
    this->rotation.z = Deg2Rad(rotation.z);
}
void Transform::SetRotationRadians(Vector3 rotation) {
    this->rotation = rotation;
}
void Transform::RotateByDegrees(Vector3 theta) {
    this->rotation.x += Deg2Rad(theta.x);
    this->rotation.y += Deg2Rad(theta.y);
    this->rotation.z += Deg2Rad(theta.z);
}
void Transform::RotateByRadians(Vector3 theta) {
    this->rotation.x += theta.x;
    this->rotation.y += theta.y;
    this->rotation.z += theta.z;
}
void Transform::SetPosition(Vector3 position) {
    this->position = position;
}
void Transform::Translate(Vector3 translation) {
    this->position.x += translation.x;
    this->position.y += translation.y;
    this->position.z += translation.z;
}