// raytracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Renderer.h"
#include <spdlog/spdlog.h>

int main()
{
    Renderer renderer{};
    renderer.set_image_size(400, 225);
    spdlog::info("Generating image...");
    renderer.generate_image();
    spdlog::info("Writing image output...");
    renderer.write_to_image("output.png");
    spdlog::info("Finished!");
}
