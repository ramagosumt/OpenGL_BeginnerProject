cmake_minimum_required(VERSION 3.30)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

# Explicitly set the include directories with full paths
include_directories(
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLEW/include"
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLFW/include"
        "B:/OpenGL Projects/LearnOpenGL/Source/Plugins"
        "B:/OpenGL Projects/LearnOpenGL/Source/Objects"
        "B:/OpenGL Projects/LearnOpenGL/Source/Helpers"
        "B:/OpenGL Projects/LearnOpenGL/Source/Scenes"
        "B:/OpenGL Projects/LearnOpenGL/Source"
)

# Add GLEW_STATIC to use static GLEW library
add_definitions(-DGLEW_STATIC)

# Explicitly set library directories
link_directories(
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLFW/lib-mingw-w64"
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLEW/lib/Release/x64"
)

# Source files
set(SOURCE_FILES Source/main.cpp
        Source/Helpers/Renderer.cpp
        Source/Helpers/Renderer.h
        Source/Objects/VertexBuffer.cpp
        Source/Objects/VertexBuffer.h
        Source/Objects/IndexBuffer.cpp
        Source/Objects/IndexBuffer.h
        Source/Objects/VertexBufferLayout.cpp
        Source/Objects/VertexBufferLayout.h
        Source/Objects/VertexArray.cpp
        Source/Objects/VertexArray.h
        Source/Objects/Shader.cpp
        Source/Objects/Shader.h
        Source/Objects/Texture.cpp
        Source/Objects/Texture.h
        Source/Objects/Camera.cpp
        Source/Objects/Camera.h
        Source/Scenes/SceneManager.cpp
        Source/Scenes/SceneManager.h
        Source/Scenes/LearnOpenGL.cpp
        Source/Scenes/LearnOpenGL.h
        Source/Scenes/LearnOpenGL_LargerMap.cpp
        Source/Scenes/LearnOpenGL_LargerMap.h
        Source/Scenes/LearnOpenGL_SimpleHouse.cpp
        Source/Scenes/LearnOpenGL_SimpleHouse.h

        Source/Plugins/imgui/imconfig.h
        Source/Plugins/imgui/imgui.cpp
        Source/Plugins/imgui/imgui.h
        Source/Plugins/imgui/imgui_demo.cpp
        Source/Plugins/imgui/imgui_draw.cpp
        Source/Plugins/imgui/imgui_impl_glfw.cpp
        Source/Plugins/imgui/imgui_impl_glfw.h
        Source/Plugins/imgui/imgui_impl_opengl3.cpp
        Source/Plugins/imgui/imgui_impl_opengl3.h
        Source/Plugins/imgui/imgui_impl_opengl3_loader.h
        Source/Plugins/imgui/imgui_internal.h
        Source/Plugins/imgui/imgui_tables.cpp
        Source/Plugins/imgui/imgui_widgets.cpp
        Source/Plugins/imgui/imstb_rectpack.h
        Source/Plugins/imgui/imstb_textedit.h
        Source/Plugins/imgui/imstb_truetype.h
        Source/Plugins/stb_image/stb_image.h
        Source/Plugins/stb_image/stb_image.cpp
)

add_executable(LearnOpenGL ${SOURCE_FILES})

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(LearnOpenGL
        ${OPENGL_LIBRARIES}  # OpenGL Libraries
        glfw3                # GLFW library
        glew32s              # Static GLEW library
        opengl32             # OpenGL library
        glu32                # GLU library
)

# Additional include directories for the target
target_include_directories(LearnOpenGL PRIVATE
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLEW/include"
        "B:/OpenGL Projects/LearnOpenGL/Dependencies/GLFW/include"
)