typedef struct {
    uint64_t start;
    uint64_t end;
    uint64_t size;
    uint16 bufferIndex; 
    bool free;
} CL_MemBlock;

typedef struct {
    CL_MemBlock mainBlock;
    CL_MemBlock vertexBlock;
    CL_MemBlock indexBlock;
    CL_MeshRef meshRef;
} CL_MeshRef;

char ReadBuffer(__global const char *heap, __global const CL_MemBlock memBlock, uint64_t index) {
    return heap[memBlock.index][memBlock.start + index];
}

__kernel void GetMeshData(__global char *heap, __global CL_MeshRef mesh, __global char *output) {

}

__kernel void Test(__global char *heap, __global CL_MemBlock memBlock, __global char *output) {
    *output = ReadBuffer(heap, memBlock, 0);
}
