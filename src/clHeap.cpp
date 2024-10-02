#include "clHeap.hpp"
#include <iostream>

void Create_CL_MemBlock(CL_MemBlock *memBlock, uint32_t start, uint32_t end, uint64_t size, bool free) {
    memBlock->start = start;
    memBlock->end = end;
    memBlock->size = size;
    memBlock->free = free;
}

CL_Heap::CL_Heap(CL_Object *clObject, VRAM_Presets size) {
    size_t allocAmount;
    size_t maxMalloc;
    // Check the maximum alloc size for your device
    clGetDeviceInfo(clObject->activeDevice.get(), CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size_t), &maxMalloc, NULL);
    if (size > maxMalloc) {
        std::cerr << "Error: Invalid OpenCL buffer size!\n" << "Desired buffer size: " << size << "\nMax buffer size: " << maxMalloc << '\n';
        exit(282);
    }
    // If CL_MaxAlloc is the specified alloc size, allocate the maximum amount of memory supported by your device
    allocAmount = (size == CL_MaxAlloc) ? maxMalloc : size;
    this->clObject = clObject;
    heap = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, allocAmount);
    // Ensure blocks only has 1 block and create a block encompassing the whole thing
    blocks.resize(1);
    Create_CL_MemBlock(&blocks[0], 0, allocAmount-1, allocAmount, true);
    if (blocks[0].size == 0) {
        std::cerr << "Could not create initial CL_MemBlock.\n";
    }
}

CL_Heap::CL_Heap(CL_Object *clObject, uint64_t size) {
    this->clObject = clObject;
    heap = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, size);
    // Ensure blocks only has 1 block and create a block encompassing the whole thing
    blocks.resize(1);
    Create_CL_MemBlock(&blocks[0],0, size-1, size, true);
    if (blocks[0].size == 0) {
        std::cerr << "Could not create initial CL_MemBlock.\n";
    }
}