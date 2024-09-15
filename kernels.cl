__kernel void Test(__global char* data) {
    char string[] = "Hello from the GPU!";
    for (int i = 0; i < sizeof(string)/sizeof(char); i++) {
        data[i] = string[i];
    }
}