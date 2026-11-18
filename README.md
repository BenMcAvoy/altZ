# altZ

altZ is a small C++23 Vulkan rendering experiment. It uses GLFW for the window, Vulkan for rendering and Dear ImGui for the interface, with a reusable engine library and a separate runtime target.

## Build and run

Install [xmake](https://xmake.io), a Vulkan SDK and the platform's Vulkan drivers. From the repository root:

```sh
xmake
xmake run altZRuntime
```

xmake resolves the GLFW, GLM, ImGui and Vulkan dependencies declared in `xmake.lua`.

## Status

This is an early renderer/engine experiment. The current runtime is a small rendering sample, not a general-purpose game engine.
