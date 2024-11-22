cmake_minimum_required(VERSION 3.12)
# note actual version used: 3.28.3

# =============================
project(revmon C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)


# Build libraries:
# =============================
set( LIB_NAME search )
add_library( ${LIB_NAME}
    ${CMAKE_SOURCE_DIR}/src/loader.hpp
    ${CMAKE_SOURCE_DIR}/src/loader.cpp
    ${CMAKE_SOURCE_DIR}/src/search.hpp
    ${CMAKE_SOURCE_DIR}/src/search.cpp
)

target_include_directories( ${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/ )


# Build Executable
# =============================
set( EXE_NAME mapsearch )
add_executable( ${EXE_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp )
target_link_libraries( ${EXE_NAME} PRIVATE ${LIB_NAME} )

# Build Tests
# =============================
# Basically just following directions at: https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md


# note: install with `apt install catch2`

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
set(TEST_TARGET test-all)
add_executable(${TEST_TARGET} 
    ${CMAKE_SOURCE_DIR}/src/test_load.cpp
    ${CMAKE_SOURCE_DIR}/src/test_search.cpp
)
target_link_libraries( ${TEST_TARGET} PRIVATE ${LIB_NAME} )
target_link_libraries( ${TEST_TARGET} PRIVATE Catch2::Catch2WithMain)
