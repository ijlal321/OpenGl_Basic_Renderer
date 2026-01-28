cmake_minimum_required(VERSION 3.15)
project(Learn_Opengl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##  Variables Definition
# ==========================================
set(SDL2_dir "${CMAKE_SOURCE_DIR}/external/SDL2")
set(SDL2_image_dir "${CMAKE_SOURCE_DIR}/external/SDL2_image_2.0")


##  Main Project Files
# ==========================================
add_executable(Learn_Opengl 
            src/main.cpp
            src/Screen.cpp
            src/Input.cpp
            src/Shader.cpp
            src/Quad.cpp
            src/Buffer.cpp
            src/Camera.cpp
            src/Texture.cpp
            src/Light.cpp
            src/Cube.cpp
            )

target_include_directories(Learn_Opengl PUBLIC ${CMAKE_SOURCE_DIR}/include)


## Adding Glad Files for Opengl Extensions
# ==========================================
target_include_directories(Learn_Opengl PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)
target_sources(Learn_Opengl PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)


##  Installing SDL2 and Linking Opengl 
# ==========================================
target_include_directories(Learn_Opengl PUBLIC ${SDL2_dir}/include)
target_link_libraries(Learn_Opengl PUBLIC 
            ${SDL2_dir}/lib/x64/SDL2.lib
            ${SDL2_dir}/lib/x64/SDL2main.lib
            opengl32
            )

# Copy SDL2.dll to the executable directory after build
add_custom_command(TARGET Learn_Opengl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_dir}/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:Learn_Opengl>
)


## Adding Glad Files for GML Library
# ==========================================
target_include_directories(Learn_Opengl PRIVATE ${CMAKE_SOURCE_DIR}/external/GLM)

## Adding SDL2_image 2.0 Files for Loading Textures
# ==========================================
target_include_directories(Learn_Opengl PRIVATE ${SDL2_image_dir}/include)

target_link_libraries(Learn_Opengl PUBLIC 
            ${SDL2_image_dir}/lib/x64/SDL2_image.lib
            )

# Copy all SDL2_image dll's to the executable directory after build
file(GLOB MYLIB_DLLS
    "${SDL2_image_dir}/lib/x64/*.dll"
)

add_custom_command(TARGET Learn_Opengl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MYLIB_DLLS}
        $<TARGET_FILE_DIR:Learn_Opengl>
)