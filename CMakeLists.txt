cmake_minimum_required(VERSION 3.2.2) # CMake version check

project(BossVsPlayer) # Create project "HackSlash"

#Flags
SET(GCC_LINK_FLAGS "-std=c++14 -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lz -lGLEW -lglut -lm -lsfml-system -lsfml-network -lpthread")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

LINK_DIRECTORIES("${CMAKE_BINARY_PATH}/lib")

include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB sources *.h *.c *.cxx *.cpp *.hxx)

add_executable(BossVsPlayer ${sources})

TARGET_LINK_LIBRARIES(BossVsPlayer ${CMAKE_SOURCE_DIR}/lib/libKlaoudeEngineLinux.a)
