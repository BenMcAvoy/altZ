set_project("altZ")

add_requires("glfw")
add_requires("glm")
add_requires("imgui v1.92.1-docking", { configs = { glfw = true, vulkan = true, freetype = true } })
add_requires("vulkan-headers")
add_requires("vulkan-loader")

set_languages("c++23")

add_rules("mode.debug", "mode.release")

target("altZEngine")
    set_kind("static")
    add_files("engine/**.cpp")
    add_includedirs("engine", { public = true })
    add_packages("glfw", "glm", "imgui", "vulkan-headers", "vulkan-loader")

target("altZRuntime")
    set_kind("binary")
    add_files("runtime/**.cpp")
    add_deps("altZEngine")
    add_packages("glfw", "glm", "imgui", "vulkan-headers", "vulkan-loader")