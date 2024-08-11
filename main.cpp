#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "RevenantVectors.hpp"
#include "RevenantTris.hpp"
#include "RevenantMesh.hpp"
#include "SerializeString.hpp"
#include "GameObject.hpp"

Mesh amongusMesh("amongusRotated.obj");
std::vector<GameObject> hierarchy;
void Start() {
}
void Input() {
}
void Predraw() {
}
void Draw() {
}
bool quit = false;
int main() {
    Start();
    std::cout << amongusMesh.triangles[4].a->x << std::endl;
    while(!quit) {
        Input();
        Predraw();
        Draw();
    }
}