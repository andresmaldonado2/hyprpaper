#include "WallpaperTarget.hpp"
#include "/home/sora/Downloads/vkvg/include/vkvg.h"

CWallpaperTarget::~CWallpaperTarget() {
    vkvg_surface_destroy(m_pVulkanSurface);
}

void CWallpaperTarget::create(const std::string& path) {
    m_szPath = path;

    const auto BEGINLOAD = std::chrono::system_clock::now();

    // need to ask vaxry if wall paper resolves here or not
    VkvgDevice VULKAN_DEVICE =vkvg_device_create(VK_SAMPLE_COUNT_1_BIT, true);
    VkvgSurface VULKAN_SURFACE = nullptr;
    if (path.find(".png") == path.length() - 4) {
        // TODO replace with sail, check to see if using memory mapped image is faster when combined with sail
        VULKAN_SURFACE = vkvg_surface_create_from_image(VULKAN_DEVICE, path.c_str());
    } /*else if (path.find(".jpg") == path.length() - 4 || path.find(".jpeg") == path.length() - 5) {
        // TODO do this jpeg stuff see which is faster
        CAIROSURFACE = JPEG::createSurfaceFromJPEG(path);
        m_bHasAlpha = false;
    } */else {
        Debug::log(CRIT, "unrecognized image %s", path.c_str());
        exit(1);
        return;
    }

    if (vkvg_surface_status(VULKAN_SURFACE) != VKVG_STATUS_SUCCESS) {
        Debug::log(CRIT, "Failed to read image %s because of:\n%s", path.c_str(), vkvg_status_to_string(vkvg_surface_status(VULKAN_SURFACE)));
        exit(1);
    }

    //m_vSize = { cairo_image_surface_get_width(CAIROSURFACE), cairo_image_surface_get_height(CAIROSURFACE) };

    const auto MS = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - BEGINLOAD).count() / 1000.f;

    Debug::log(LOG, "Preloaded target %s in %.2fms", path.c_str(), MS);

    m_pVulkanSurface = VULKAN_SURFACE;
    m_pVulkanDevice = VULKAN_DEVICE;
}