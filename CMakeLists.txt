# Minimal CMake version required
cmake_minimum_required(VERSION 3.10)

# 1. Project and Version
project(Physics_Engine VERSION 1.0.0)

# 2. Dependency
# - SDL2
find_package(SDL2 REQUIRED)
# - Math library (pour sqrt, etc.)
find_library(LIB_MATH m)

# 3. Compiling
add_executable(Engine
    src/main.c
    src/physics.c
)

# --- STATIC CODE ANALYSIS SETUP (CPPCHECK) ---
# On cherche si l'outil est installé sur la machine
find_program(CPPCHECK_EXE cppcheck)

if(CPPCHECK_EXE)
    message(STATUS "Static Code Analysis enabled: Cppcheck found at ${CPPCHECK_EXE}")
    
    # On configure les règles d'analyse :
    # --enable=... : Active les avertissements, les conseils de performance, le style, etc.
    # --suppress=... : Ignore les erreurs liées aux fichiers système (comme SDL2 qu'on ne contrôle pas)
    # --inconclusive : Pour aller plus loin (optionnel)
    set_target_properties(Engine PROPERTIES
        C_CPPCHECK "${CPPCHECK_EXE};--enable=warning,performance,portability,style;--suppress=missingIncludeSystem"
    )
else()
    message(WARNING "Cppcheck not found! Please install it (sudo apt install cppcheck)")
endif()
# ---------------------------------------------

# 4. Linking
# - Linking SDL2 and Math library
target_link_libraries(Engine PRIVATE SDL2::SDL2 ${LIB_MATH})

# 5. Install configuration (Copie config.txt automatiquement)
configure_file(${CMAKE_SOURCE_DIR}/config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)

# 6. Install libraries
install (TARGETS Engine DESTINATION bin)
include(CPack)