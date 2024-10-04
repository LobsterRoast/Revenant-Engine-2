#include "clIntegration.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "ConsoleInputs.hpp"

int clSetup(CL_Object* clObject) {
    std::string platformName;
    // Set the active platform
    cl::Platform::get(&clObject->compatiblePlatforms); // Populate clObject->compatiblePlatforms with all the installed platforms on the user's device
    int platformCount = clObject->compatiblePlatforms.size();
    if (platformCount == 1) { // If only 1 platform is found, make it the active platform
        clObject->activePlatform = clObject->compatiblePlatforms.front();
        clObject->activePlatform.getInfo(CL_PLATFORM_NAME, &platformName);
        std::cout << "Platform found!\nPlatform name: " + platformName + "\nActive platform: " + platformName << std::endl;
    }
    else if (platformCount > 1) { // If multiple platforms are found, have the user input which one they would like to use
        std::cout << "Multiple platforms found! Please specify a platform to use.\n" << std::endl;
        for(int i = 0; i < platformCount; i++) {
            clObject->compatiblePlatforms[i].getInfo(CL_PLATFORM_NAME, &platformName);
            std::cout << std::to_string(i) + " - " + platformName + '\n';
        }
        std::cout << std::flush;
        clObject->activePlatform = clObject->compatiblePlatforms[cinInteger("Please input the index of your desired OpenCL platform.\n",
                                                                            "Platform at the specified index does not exist. Please input a valid index.\n")];
        clObject->activePlatform.getInfo(CL_PLATFORM_NAME, &platformName);
        std::cout << "Active platform: " + platformName << std::endl;
    }
    else {
        std::cerr << "No platforms compatible with OpenCL found. Please ensure you have a compatible OpenCL runtime installed." << std::flush;
        return 1;
    }

    // Set the active device
    clObject->activePlatform.getDevices(CL_DEVICE_TYPE_GPU, &clObject->compatibleDevices); // Populate clObject->compatibleDevices with all usable devices
    int deviceCount = clObject->compatibleDevices.size();
    std::cout << std::to_string(deviceCount) + " device(s) found.\n";
    if (deviceCount == 1) { // If only 1 device is found, make it the active platform
        std::string deviceName;
        clObject->activeDevice = clObject->compatibleDevices.front();
        clObject->activeDevice.getInfo(CL_DEVICE_NAME, &deviceName);
        std::cout << "Device name: " + deviceName + "\nActive device: " + deviceName << std::endl;
    }
    else if (deviceCount > 1) { // If multiple devices are found, have the user input which one they would like to use
        std::string deviceName;
        std::cout << "Please specify a device to use.\n" << std::flush;
        for(int i = 0; i < deviceCount; i++) {
            clObject->compatibleDevices[i].getInfo(CL_DEVICE_NAME, &deviceName);
            std::cout << std::to_string(i) + " - " + deviceName + '\n';
        }
        std::cout << std::flush;
        clObject->activeDevice = clObject->compatibleDevices[cinInteger("Please input the index of your desired device.\n",
                                                        "Device at the specified index does not exist. Please input a valid index.\n")];
        clObject->activeDevice.getInfo(CL_DEVICE_NAME, &deviceName);
        std::cout << "Active device: " + deviceName << std::endl;
    }
    else { 
        std::cerr << "No platforms compatible with OpenCL found. Please ensure you have a compatible device." << std::flush;
        return 1;
    }
    clObject->vendor = clObject->activeDevice.getInfo<CL_DEVICE_VENDOR>();
    std::cout << "Device vendor: " + clObject->vendor << std::endl;
    clObject->version = clObject->activeDevice.getInfo<CL_DEVICE_VERSION>();
    std::cout << "Device version: " + clObject->version << std::endl;
    clObject->kernelFile = std::ifstream("src/kernels.cl");
    if (clObject->kernelFile.is_open()) std::cout << "Kernel file successfully opened." << std::endl;
    else {
        std::cout << "Couldn't open kernels.cl. Terminating the program." << std::endl;
        return 1;
    }
    clObject->src = new std::string(std::istreambuf_iterator<char>(clObject->kernelFile), (std::istreambuf_iterator<char>()));
    clObject->sources.push_back({clObject->src->c_str(), clObject->src->length() + 1});
    clObject->context = cl::Context(clObject->activeDevice);
    clObject->program = cl::Program(clObject->context, clObject->sources);
    clObject->program.build("-cl-std=CL3.0");
    return 0;
}
