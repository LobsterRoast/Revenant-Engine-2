#include "clHeap.hpp"

CL_MemBlock::CL_MemBlock(uint32_t start, uint32_t end, uint32_t size, bool free)
: start(start), end(end), size(size), free(free) {}

CL_Heap::CL_Heap(CL_Object clObject, VRAM_Presets size) {
    heap = cl::Buffer(clObject.context, CL_MEM_READ_WRITE, size);
    blocks.resize(1);
    blocks[0] = CL_MemBlock(0, size-1, size, true);
}

CL_Heap::CL_Heap(CL_Object clObject, uint32_t size) {
    heap = cl::Buffer(clObject.context, CL_MEM_READ_WRITE, size);
    blocks.resize(1);
    blocks[0] = CL_MemBlock(0, size-1, size, true);
}