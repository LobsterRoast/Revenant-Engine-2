#ifndef CL_HEAP_ALLOCATOR
#define CL_HEAP_ALLOCATOR
#include "clIntegration.hpp"
#include <vector>

enum VRAM_Presets {
    CL_1Gb = 1073741824,
    CL_2Gb = 2147483648,
    CL_4Gb = 4294967296,
    CL_6Gb = 6442450944,
    CL_8Gb = 8589934592,
    CL_10Gb = 10737418240
};

class CL_MemBlock {
    public:
        uint32_t start;
        uint32_t end;
        uint32_t size;
        bool free;
        CL_MemBlock() : start(0), end(0), size(0), free(true) {}
        CL_MemBlock(uint32_t start, uint32_t end, uint32_t size, bool free);
};

class CL_Heap {
    public:
        cl::Buffer heap;
        std::vector<CL_MemBlock> blocks;
        CL_Heap(CL_Object clObject, VRAM_Presets size);
        CL_Heap(CL_Object clObject, uint32_t size);
        template <typename T>
        CL_MemBlock GetHeapBlock(T var) {
            uint32_t memSize = sizeof(var);
            for(int i = 0; i < blocks.size(); i++) {
                // Check to see if there is an available block of memory to store the specified var in
                if (blocks[i].size >= memSize && blocks[i].free == true) {
                    // Creates a memBlock perfectly sized to hold your variable
                    CL_MemBlock memBlock = CL_MemBlock(
                        blocks[i].start, 
                        (blocks[i].start+memSize)-1,  
                        ((blocks[i].start+memSize)-1) - (blocks[i].start), 
                        false
                    );
                    // Determine how much free memory is left in the now occupied memory block
                    CL_MemBlock remainder = CL_MemBlock(
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
                    // Return the requested block of VRAM
                    return memBlock;
                }
            }
        }
    private:
        template <typename T>
        int AllocToHeap(CL_MemBlock memBlock, T var) {
            return 0;
        }

};


#endif
