#pragma once
#include <cstdint>
#include <string_view>
#include <memory>
#include "Image.h"

class Renderer
{
public:
    void set_image_size(int32_t width, int32_t height) {
        m_width = width;
        m_height = height;
    }
    void generate_image();
    void write_to_image(const std::string_view& path);
    
private:
    int32_t m_width = 200;
    int32_t m_height = 200;
    Image m_image = Image{};
};

