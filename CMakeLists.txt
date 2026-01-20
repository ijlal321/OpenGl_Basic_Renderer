cmake_minimum_required(VERSION 3.15)
project(Learn_Opengl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_dir "${CMAKE_SOURCE_DIR}/external/SDL2")

add_executable(Learn_Opengl 
            src/main.cpp
            src/screen.cpp
            )

target_include_directories(Learn_Opengl PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Installing SDL2 and Linking Opengl 
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