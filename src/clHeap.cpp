#include "clHeap.hpp"
#include <iostream>

void Create_CL_MemBlock(CL_MemBlock *memBlock, uint64_t start, uint64_t end, uint64_t size, bool free) {
    memBlock->start = start;
    memBlock->end = end;
    memBlock->size = size;
    memBlock->free = free;
}

CL_Heap::CL_Heap(CL_Object *clObject, VRAM_Presets size) {
    this->clObject = clObject;
    queue = cl::CommandQueue(clObject->context, clObject->activeDevice);
    size_t remainingAllocSize = size;
    // Check the maximum alloc size for your device
    clGetDeviceInfo(clObject->activeDevice.get(), CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size_t), &maxMalloc, NULL);
    maximumMallocBuffer = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, sizeof(maxMalloc));
    queue.enqueueWriteBuffer(maximumMallocBuffer, CL_TRUE, 0, sizeof(maxMalloc), &maxMalloc);
    for (int i = 0; i < 4; i++) {
        size_t allocSize = remainingAllocSize;
        allocSize = remainingAllocSize > maxMalloc ? maxMalloc : remainingAllocSize;
        remainingAllocSize -= allocSize;
        heapQuad[i] = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, allocSize);
    }
    // Ensure blocks only has 1 block and create a block encompassing the whole thing
    blocks.resize(1);
    Create_CL_MemBlock(&blocks[0], 0, size-1, size, true);
    if (blocks[0].size == 0) {
        std::cerr << "Could not create initial CL_MemBlock.\n";
    }
    heap = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, sizeof(cl_mem) * 4, heapQuad, &err);
}

CL_Heap::CL_Heap(CL_Object *clObject, uint64_t size) {
    queue = cl::CommandQueue(clObject->context, clObject->activeDevice);
    size_t remainingAllocSize = size;
    // Check the maximum alloc size for your device
    clGetDeviceInfo(clObject->activeDevice.get(), CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(size_t), &maxMalloc, NULL);
    for (int i = 0; i < 4; i++) {
        size_t allocSize = remainingAllocSize;
        allocSize = remainingAllocSize > maxMalloc ? maxMalloc : remainingAllocSize;
        remainingAllocSize -= allocSize;
        heapQuad[i] = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, allocSize);
    }
    // Ensure blocks only has 1 block and create a block encompassing the whole thing
    blocks.resize(1);
    Create_CL_MemBlock(&blocks[0], 0, size-1, size, true);
    if (blocks[0].size == 0) {
        std::cerr << "Could not create initial CL_MemBlock.\n";
    }
    heap = cl::Buffer(clObject->context, CL_MEM_READ_WRITE, sizeof(cl_mem) * 4, heapQuad, &err);
}

void CL_Heap::TestCL() {
    char testChar = 'B';
    CL_MemBlock myMemBlock = GetHeapBlock<char>(testChar);
    char buf;
    cl::Buffer memBuf(clObject->context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    cl::Buffer memBlockBuf(clObject->context, CL_MEM_READ_WRITE, sizeof(myMemBlock));
    cl::Kernel kernel(clObject->program, "Test", &err);
    kernel.setArg(0, heap);
    kernel.setArg(1, memBlockBuf);
    kernel.setArg(2, memBuf);
    cl::CommandQueue queue(clObject->context, clObject->activeDevice);
    cl::NDRange globalWorkSize(1);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalWorkSize, cl::NullRange);
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buf), &buf);
    std::cout << buf << std::endl;
}