#pragma once

#include "../defines.hpp"

class CWallpaperTarget;

struct SPoolBuffer {
    wl_buffer* buffer = nullptr;
    VkvgDevice device = nullptr; 
    VkvgSurface surface = nullptr;
    VkvgContext vkvg = nullptr;
    void* data = nullptr;
    size_t size = 0;
    std::string name = "";

    std::string target = "";
    Vector2D pixelSize;
};