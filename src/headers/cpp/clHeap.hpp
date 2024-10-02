#ifndef CL_HEAP_ALLOCATOR
#define CL_HEAP_ALLOCATOR
#include "clIntegration.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <string>

enum VRAM_Presets {
    CL_1Gb = 1073741824,
    CL_2Gb = 2147483648,
    CL_4Gb = 4294967296,
    CL_6Gb = 6442450944,
    CL_8Gb = 8589934592,
    CL_10Gb = 10737418240,
};

typedef struct {
    public:
        uint64_t start;
        uint64_t end;
        uint64_t size;
        bool free;
} CL_MemBlock;

void Create_CL_MemBlock(CL_MemBlock *memBlock, uint32_t start, uint32_t end, uint64_t size, bool free);

class CL_Heap {
    public:
        cl::CommandQueue queue;
        CL_Object *clObject;
        size_t maxMalloc;
        cl::Buffer maximumMallocBuffer;
        // Because OpenCL places a maximum size restriction on buffers, 4 buffers are created that can be indexed into at runtime.
        cl::Buffer heap[4];
        std::vector<CL_MemBlock> blocks;
        CL_Heap(CL_Object *clObject, VRAM_Presets size);
        CL_Heap(CL_Object *clObject, uint64_t size);
        template <typename T>
        CL_MemBlock GetHeapBlock(T var) {
            CL_MemBlock memBlock;
            size_t memSize = sizeof(T);
            for(int i = 0; i < blocks.size(); i++) {
                // Check to see if there is an available block of memory to store the specified var in
                if (blocks[i].size >= memSize && blocks[i].free == true) {
                    CL_MemBlock remainder;
                    // Creates a memBlock perfectly sized to hold your variable
                    Create_CL_MemBlock(
                        &memBlock,
                        blocks[i].start, 
                        (blocks[i].start+memSize)-1,  
                        memSize,
                        false
                    );
                    // Determine how much free memory is left in the now occupied memory block
                    Create_CL_MemBlock(
                        &remainder,
                        memBlock.end + 1,
                        blocks[i].end,
                        blocks[i].size - memBlock.size,
                        true
                    );
                    // If the amount of free memory left is 0, add another memory block to blocks.
                    if (remainder.size > 0) {
                        blocks.resize(blocks.size()+1);
                        blocks.insert(blocks.begin() + (i + 1), remainder);
                    }
                    blocks[i] = memBlock;
                    // Write the user's data into the heap
                    AllocToHeap<T>(clObject, memBlock, var);
                    // Return the requested block of VRAM
                    return memBlock;
                }
            }
            Create_CL_MemBlock(
                &memBlock,
                0,
                0,
                0,
                false
            );
            return memBlock;
        }
    private:
        cl_int err = 0;
        template <typename T>
        int AllocToHeap(CL_Object *clObject, CL_MemBlock memBlock, T var) {
            // Determine whether the beginning and end of the memBlock point to different parts of the heap (that is different buffer indices)
            unsigned short startIndex = (unsigned short)std::floor(memBlock.start/maxMalloc);
            unsigned short endIndex = (unsigned short)std::floor(memBlock.end/maxMalloc);
            // Check to see if the start and end of the MemBlock span different parts of the heap
            if (startIndex == endIndex) {
            // Write var into the part of the heap specified by its CL_MemBlock
                err = queue.enqueueWriteBuffer(heap[startIndex], CL_TRUE, memBlock.start, memBlock.size, &var);
                if(err != 0) {
                    std::cerr << "Something went wrong." << '\n' << "Error Code: " << err + '\n';
                }
                return 0;
            } 
            else {
                size_t indexAStart = 0;
                size_t indexAEnd = maxMalloc-1 - memBlock.start; // Max malloc is a size, so remove 1 to make it an index.
                size_t indexASize = maxMalloc - memBlock.start+1; // memBlock.start is an index, so add 1 to make it a size.
                size_t indexBStart = indexASize;
                size_t indexBSize = memBlock.size - indexASize;
                std::string dataBuffer(reinterpret_cast<char*>(&var), sizeof(var));
                const char *dataBufferA = dataBuffer.substr(indexAStart, indexASize).c_str();
                const char *dataBufferB = dataBuffer.substr(indexBStart, indexBSize).c_str();
                err = queue.enqueueWriteBuffer(heap[startIndex], CL_TRUE, memBlock.start, indexASize, dataBufferA);
                if(err != 0) {
                    std::cerr << "Something went wrong." << '\n' << "Error Code: " << err + '\n';
                }
                err = queue.enqueueWriteBuffer(heap[endIndex], CL_TRUE, 0, indexBSize, dataBufferB);
                if(err != 0) {
                    std::cerr << "Something went wrong." << '\n' << "Error Code: " << err + '\n';
                }
            }
        }
};


#endif
 