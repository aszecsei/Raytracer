#pragma once
#include "Vec3.h"
#include <memory>

class Image
{
public:
    Image() {}

    Image(int32_t width, int32_t height) :
        m_width(width), m_height(height) {
        pixels = std::make_unique<Color[]>(width * height);
    }

    Color at(int x, int y) const {
        return pixels[y * m_width + x];
    }
    Color& at(int x, int y) {
        return pixels[y * m_width + x];
    }

    inline int32_t width() const { return m_width; }
    inline int32_t height() const { return m_height; }

    std::unique_ptr<uint8_t[]> bytes() const {
        auto result = std::make_unique<uint8_t[]>(m_width * m_height * Color::CHANNELS);

        for (int i = 0; i < m_width * m_height; i++) {
            pixels[i].copy_bytes(&result[i * Color::CHANNELS]);
        }

        return result;
    }

private:
    int32_t m_width = 0;
    int32_t m_height = 0;
    std::unique_ptr<Color[]> pixels = nullptr;
};

