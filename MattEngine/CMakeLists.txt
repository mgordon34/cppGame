cmake_minimum_required(VERSION 3.8)

set(ENGINE_SRC
        Camera2D.cpp
        Camera2D.h
        collisionBox.cpp
        collisionBox.h
        GLSLProgram.cpp
        GLSLProgram.h
        ImageLoader.cpp
        ImageLoader.h
        InputManager.cpp
        InputManager.h
        ResourceManager.cpp
        ResourceManager.h
        sprite.cpp
        sprite.h
        SpriteBatch.cpp
        SpriteBatch.h
        spritesheet.cpp
        spritesheet.h
        TextureCache.cpp
        TextureCache.h
        vector2.cpp
        vector2.h
        vertex.h
        window.cpp
        window.h)

add_library(MattEngine STATIC ${ENGINE_SRC})

#find_package(glfw3 REQUIRED)
#target_link_libraries(MattEngine glfw3)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(MattEngine ${GLFW_LIBRARIES})
target_link_libraries(MattEngine ${GLFW_STATIC_LIBRARIES})

find_package(OPENGL REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

target_include_directories(MattEngine PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(MattEngine ${OPENGL_gl_LIBRARY})
target_link_libraries(MattEngine ${OPENGL_glu_LIBRARY})

target_link_libraries(MattEngine GLEW)

#target_link_libraries(MattEngine SOIL)
find_library(COREFOUNDATION_LIBRARY CoreFoundation)
target_link_libraries(MattEngine ${COREFOUNDATION_LIBRARY})

find_library(SOIL_LIB SOIL)
target_link_libraries(MattEngine ${SOIL_LIB})
