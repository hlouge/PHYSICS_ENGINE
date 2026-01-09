cmake_minimum_required(VERSION 3.10)
project(Physics_Engine VERSION 1.0.0)

# --- DEPENDENCIES ---
find_package(SDL2 REQUIRED)
find_library(LIB_MATH m)
find_program(CPPCHECK_EXE cppcheck)

# --- 1. LIBRAIRIE PHYSIQUE (Core logic) ---
# On crée une librairie statique qui contient juste la logique, sans le main
add_library(PhysicsCore src/physics.c)
target_link_libraries(PhysicsCore ${LIB_MATH})

# --- 2. EXECUTABLE (Simulation visuelle) ---
add_executable(Engine src/main.c)
target_link_libraries(Engine PRIVATE PhysicsCore SDL2::SDL2)

# --- 3. ANALYSE STATIQUE ---
if(CPPCHECK_EXE)
    set_target_properties(Engine PROPERTIES C_CPPCHECK "${CPPCHECK_EXE};--enable=warning,performance,portability,style;--suppress=missingIncludeSystem")
endif()

# --- 4. TESTS UNITAIRES ---
enable_testing()
add_executable(UnitTests tests/test_physics.c)
target_link_libraries(UnitTests PRIVATE PhysicsCore)
add_test(NAME PhysicsTest COMMAND UnitTests)

# On crée un exécutable dédié aux tests
add_executable(UnitTests tests/test_physics.c)
target_link_libraries(UnitTests PRIVATE PhysicsCore)

# On enregistre le test dans CTest
add_test(NAME PhysicsLogicTest COMMAND UnitTests)

# --- INSTALL & PACKAGING ---
configure_file(${CMAKE_SOURCE_DIR}/config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)
install(TARGETS Engine DESTINATION bin)
include(CPack)