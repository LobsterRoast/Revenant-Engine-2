#ifndef LOB_LIB_HEADER
#define LOB_LIB_HEADER

#include "RevenantVectors.h"
#include "RevenantTris.h"
#include "SerializeString.hpp"
#include "RevenantMesh.hpp"
#include "clIntegration.hpp"
#include "framebuffer.h"
#include "clHeap.hpp"
#include <SDL2/SDL.h>

#define to_half fp16_ieee_from_fp32_value
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200

class LLCore {
    private:
        SDL_Window *sdlWindow;
        SDL_Renderer *sdlRenderer;
        SDL_Surface *sdlSurface;
        CL_Object clObject;
        cl::Buffer clFramebuffer;
        int *pWindowWidth;
        int *pWindowHeight;
        int w;
        int h;
        
        int InitializeSDL();
        int InitializeOpenCL();
        int CL_Execution(Pixel *framebuffer);
    public:
        bool quit;
        int LLCoreStart();
        int LLCoreInput();
        int LLCoreLoop();
        int LLCoreExit();

};
#endif