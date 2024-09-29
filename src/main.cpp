#include <iostream>
#include <vector>
#include "LobLib.hpp"
#include "GameObject.hpp"
#define to_half fp16_ieee_from_fp32_value

LLCore core;
LowDtlMesh amongusMesh;
std::vector<GameObject> hierarchy;

void Start() {
    core.LLCoreStart();
}
void Input() {
    core.LLCoreInput();
}
void Predraw() {
}
void Draw() {
    core.LLCoreLoop();
}
int main() {
    Start();
    while(!core.quit) {
        Input();
        Predraw();
        Draw();
    }
    core.LLCoreExit();
    return 0;
}