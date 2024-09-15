#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "RevenantVectors.h"
#include "RevenantTris.h"
#include "RevenantMesh.hpp"
#include "SerializeString.hpp"
#include "GameObject.hpp"
#include "clIntegration.hpp"
#define to_half fp16_ieee_from_fp32_value

bool quit = false;
CL_Object clObject;
Mesh amongusMesh("amongusRotated.obj");
std::vector<GameObject> hierarchy;
void Start() {
    if (clSetup(&clObject) != 0) {
        quit = true;
    }
    char buf[1024];
    cl_int err;
    cl::Buffer memBuf(clObject.context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    cl::Kernel kernel(clObject.program, "Test", &err);
    kernel.setArg(0, memBuf);
    cl::CommandQueue queue(clObject.context, clObject.activeDevice);
    cl::NDRange globalWorkSize(1);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalWorkSize, cl::NullRange);
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buf), buf);
    std::cout << buf << std::endl;
}
void Input() {
}
void Predraw() {
}
void Draw() {
}
int main() {
    Start();
    while(!quit) {
        Input();
        Predraw();
        Draw();
    }
}