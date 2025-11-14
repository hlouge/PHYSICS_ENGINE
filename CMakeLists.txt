# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)

#1. Project and Version
project(Physics_Engine VERSION 1.0.0)

#2. Dependency
    # - SDL2
find_package(SDL2 REQUIRED)

#3. Compiling
add_executable(Engine
    src/main.c
    src/physics.c
)

#4. Linking
    # - Linking SDL2
target_link_libraries(Engine PRIVATE SDL2::SDL2)

#5. Install librairies
install (TARGETS Engine DESTINATION bin)
include(CPack)
set(CPACK_GENERATOR "TGZ;ZIP")

set(CPACK_PACKAGE_VENDOR "Engine")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple physics Engine project")