#pragma once

#include <cstdint>

namespace config {
    constexpr uint32_t leftBound           = 0; 
    constexpr uint32_t topBound            = 0; 
    constexpr uint32_t rightBound          = 1280; 
    constexpr uint32_t bottomBound         = 1000; 
    constexpr uint32_t playerTextureHeight = 32;
    constexpr uint32_t playerTextureWidth  = 32;
    constexpr float    cameraZoomLevel     = 0.5f; 
    constexpr float    shootingDelay       = 0.2f;
    constexpr float    projectileSpeed     = 150.f;
}
