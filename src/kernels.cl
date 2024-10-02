typedef struct {
    public:
        uint32_t start;
        uint32_t end;
        uint64_t size;
        bool free;
} CL_MemBlock;

__kernel void Test(__global char* data) {
    char string[] = "Hello from the GPU!";
    for (int i = 0; i < sizeof(string)/sizeof(char); i++) {
        data[i] = string[i];
    }
}

