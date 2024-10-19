#ifndef FRAMEBUFFER_HEADER
#define FRAMEBUFFER_HEADER

typedef struct {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t a;
} Pixel;

int WriteToFramebuffer(int x, int y, Pixel pixel, Pixel framebuffer[]);

#endif