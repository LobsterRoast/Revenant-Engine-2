#include "LobLib.hpp"


int LLCore::InitializeSDL() {
    // Open an SDL Window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL." << std::endl;
        exit(1);
    }
    sdlWindow = SDL_CreateWindow("Revenant", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, 1, SDL_RENDERER_SOFTWARE);
    sdlSurface = SDL_GetWindowSurface(sdlWindow);

    if (sdlWindow == nullptr) {
        std::cerr << "Could not create a window." << std::endl;
        exit(1);
    }
    return 0;
}

int LLCore::InitializeOpenCL() {
    // Sets up OpenCL using a clObject
    // This method currently contains a test kernel used for debugging.
    // Remove it when other kernels start working.
    if (clSetup(&clObject) != 0) {
        quit = true;
    }
    char buf[1024];
    cl_int err;
    // Creates a buffer (location in VRAM)
    cl::Buffer memBuf(clObject.context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    // Creates a kernel (GPU function)
    cl::Kernel kernel(clObject.program, "Test", &err);
    // Specifies an index, representing a kernel argument that you want to pass a buffer to.
    kernel.setArg(0, memBuf);
    cl::CommandQueue queue(clObject.context, clObject.activeDevice);
    // Only open 1 thread of the kernel
    cl::NDRange globalWorkSize(1);
    // Run the kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalWorkSize, cl::NullRange);
    // Read the info stored in the buffer back into host mem
    queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buf), buf);
    std::cout << buf << std::endl;
    return 0;
}

int LLCore::CL_Execution(Pixel *framebuffer) {
    clFramebuffer = cl::Buffer(clObject.context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(Pixel) * w * h);
    cl::CommandQueue queue(clObject.context, clObject.activeDevice);
    cl::NDRange globalWorkSize(1);
    // Execute code on the GPU here...
    queue.enqueueReadBuffer(clFramebuffer, CL_TRUE, 0, sizeof(Pixel) * w * h, framebuffer);
    return 0;
}

int LLCore::LLCoreStart() {
    quit = false;
    InitializeSDL();
    InitializeOpenCL();
    return 0;
}

int LLCore::LLCoreInput() {
    // If player tries to quit, set quit to true. This will close the application if set up correctly.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
    return 0;
}

int LLCore::LLCoreLoop() {
    // Initializes pointers to the width and height of the window
    pWindowWidth = &w;
    pWindowHeight = &h;
    // Get the width and height of the window at runtime in case the user resizes the window
    SDL_GetWindowSizeInPixels(sdlWindow, pWindowWidth, pWindowHeight);
    // Creates a framebuffer in the heap. If the memory was stored in the stack, it could cause a stack overflow.
    Pixel *framebuffer = new Pixel[w*h];
    // Execute all GPU calculations
    CL_Execution(framebuffer);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    for(int i = 0; i < w * h; i++) {
        SDL_SetRenderDrawColor(sdlRenderer, framebuffer[i].r, framebuffer[i].g, framebuffer[i].b, framebuffer[i].a);
        SDL_RenderDrawPoint(sdlRenderer, i%w, i/w);
    }
    delete[] framebuffer;
    return 0;
}

int LLCore::LLCoreExit() { 
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    
    return 0;
}

