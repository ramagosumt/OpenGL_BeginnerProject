# OpenGL Rendering Framework

### Modern OpenGL | C++ | Graphics Programming

This project was developed as a graphics programming learning project focused on understanding how modern rendering pipelines are constructed using OpenGL and C++.

Rather than relying entirely on engine abstractions, the project explores lower-level rendering concepts including buffers, shaders, textures, cameras, scene management, and rendering architecture.

The project evolved from simple rendering experiments into a reusable rendering framework supporting multiple scenes and runtime debugging tools.

---

# Programming Portfolio Notes

This repository is submitted as a programming portfolio sample focused on graphics programming, rendering architecture, and modern OpenGL development.

The project demonstrates my understanding of GPU rendering pipelines, graphics abstractions, shader management, scene organization, and interactive debugging workflows.

For code reviewers, I recommend starting with the **Architecture Highlights** and **Code Review Guide** sections.

---

# Why This Project

I selected this project because it demonstrates my foundation in graphics programming and low-level rendering systems.

Unlike engine-based projects, this repository exposes the underlying systems responsible for rendering geometry, managing shaders, handling camera transformations, and communicating with the GPU.

The project demonstrates:

- Modern OpenGL rendering
- Graphics pipeline fundamentals
- Shader programming
- Buffer management
- Camera systems
- Texture loading
- Scene management
- Runtime debugging tools
- Rendering abstraction design

---

# Core Architecture

The project is organized into several layers:

```text
Rendering Layer
Graphics Resources
Scene Management
Camera System
Debug Tooling
```

Major source folders:

```text
Helpers/
    Renderer

Objects/
    Camera
    Shader
    Texture
    VertexBuffer
    IndexBuffer
    VertexArray
    VertexBufferLayout

Scenes/
    SceneManager
    LearnOpenGL
    LargerMap
    SimpleHouse

Plugins/
    ImGui
    GLM
    stb_image
```

---

# Architecture Highlights

## Rendering Abstraction Layer

The rendering layer separates graphics API calls from scene-specific logic.

Core classes include:

- Renderer
- VertexBuffer
- IndexBuffer
- VertexArray
- VertexBufferLayout

Benefits:

- Cleaner rendering code
- Reusable abstractions
- Reduced OpenGL boilerplate

---

## Shader Management

Shader compilation and usage are encapsulated within a dedicated Shader class.

Responsibilities include:

- Shader loading
- Compilation
- Linking
- Uniform management

Benefits:

- Centralized shader control
- Easier debugging
- Reusable rendering workflow

---

## Camera System

A dedicated Camera class manages:

- View transformations
- Camera movement
- Projection updates

Benefits:

- Scene-independent camera control
- Reusable navigation system
- Better separation of concerns

---

## Texture Pipeline

Texture loading is implemented using stb_image and wrapped through a Texture abstraction.

Benefits:

- Simplified asset loading
- Consistent texture management
- Encapsulation of OpenGL texture operations

---

## Scene Management

The project supports multiple rendering demonstrations through a SceneManager architecture.

Included scenes:

- LearnOpenGL
- SimpleHouse
- LargerMap

Benefits:

- Modular experimentation
- Reusable rendering infrastructure
- Easy expansion of future scenes

---

## Runtime Debugging Tools

ImGui is integrated for runtime debugging and parameter adjustment.

Benefits:

- Real-time inspection
- Faster iteration
- Visualization of rendering behavior

---

# Code Review Guide

Recommended files to inspect first:

---

## Rendering Layer

### Files

- `Helpers/Renderer.h`
- `Helpers/Renderer.cpp`

### Concepts Demonstrated

- Rendering abstraction
- Draw call management
- OpenGL workflow organization

---

## Shader System

### Files

- `Objects/Shader.h`
- `Objects/Shader.cpp`

### Concepts Demonstrated

- Shader compilation
- Program linking
- Uniform management

---

## Camera System

### Files

- `Objects/Camera.h`
- `Objects/Camera.cpp`

### Concepts Demonstrated

- View matrices
- Camera movement
- Projection control

---

## Buffer Architecture

### Files

- `Objects/VertexBuffer.*`
- `Objects/IndexBuffer.*`
- `Objects/VertexArray.*`
- `Objects/VertexBufferLayout.*`

### Concepts Demonstrated

- GPU resource management
- Vertex layouts
- Buffer organization
- Rendering pipeline fundamentals

---

## Scene Management

### Files

- `Scenes/SceneManager.h`
- `Scenes/SceneManager.cpp`
- `Scenes/LearnOpenGL.*`
- `Scenes/LearnOpenGL_SimpleHouse.*`
- `Scenes/LearnOpenGL_LargerMap.*`

### Concepts Demonstrated

- Scene organization
- Rendering workflows
- Modular graphics architecture

---

# Build Instructions

Requirements:

- Visual Studio 2022
- OpenGL
- GLFW
- GLM
- stb_image
- ImGui

Setup:

1. Clone repository
2. Open Visual Studio solution
3. Build project
4. Run executable

---

# Features

| Feature | Status |
|----------|----------|
| OpenGL Rendering | Complete |
| Shader System | Complete |
| Camera Controls | Complete |
| Texture Loading | Complete |
| Scene Management | Complete |
| ImGui Debugging | Complete |

---

# Scope Note

This project was developed as a graphics programming learning project and focuses on understanding the systems that power modern rendering engines. The emphasis is on architecture and graphics fundamentals rather than creating a finished game.
---

Developed by **@ramagosumt**
