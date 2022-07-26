#pragma once

#include "../defines.hpp"
#include "../helpers/Jpeg.hpp"

class CWallpaperTarget {
public:

    ~CWallpaperTarget();
    
    void        create(const std::string& path);
    void        render();

    std::string m_szPath;

    Vector2D    m_vSize;

    bool        m_bHasAlpha = true;

    VkvgSurface m_pVulkanSurface;
    VkvgDevice m_pVulkanDevice;
};