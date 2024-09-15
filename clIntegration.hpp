#ifndef CL_INTEGRATION_HPP
#define CL_INTEGRATION_HPP
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>
#include <vector>
#include <string>
#include <fstream>
class CL_Object {
    public:
        std::vector<cl::Platform> compatiblePlatforms;
        std::vector<cl::Device> compatibleDevices;
        cl::Platform activePlatform;
        cl::Device activeDevice;
        std::string vendor;
        std::string version;
        std::ifstream kernelFile;
        std::string* src;
        cl::Program::Sources sources;
        cl::Context context;
        cl::Program program;
};
int clSetup(CL_Object* clObject);

#endif