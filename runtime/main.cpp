#include <altz/altz.h>
#include <iostream>
#include <exception>

int main() {
    try {
        altZ::App app(800, 600, "altZ Vulkan App");
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}