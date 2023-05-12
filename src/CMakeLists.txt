cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
                    -pedantic \
                    -pedantic-errors \
                    -Wall \
                    -Wfloat-equal \
                    -Wextra \
                    -Winline \
                    -Winvalid-pch \
                    -Wcast-align \
                    -Wcast-qual \
                    -Wdisabled-optimization \
                    -Wformat=2 \
                    -Winit-self \
                    -Wlogical-op \
                    -Wmissing-declarations \
                    -Wold-style-cast \
                    -Woverloaded-virtual \
                    -Wredundant-decls \
                    -Wshadow \
                    -Wsign-promo \
                    -Wstrict-null-sentinel \
                    -Wstrict-overflow=5 \
                    -Walloc-zero \
                    -Wimplicit-fallthrough \
                    -Wunused \
                    -Wuninitialized \
                    -Winvalid-memory-model \
                    -Wmaybe-uninitialized \
                    -Warray-bounds=2 \
                    -Warray-parameter=2 \
                    -Wswitch \
                    -Werror \
                    -ggdb3"
    CACHE STRING "Default CXX options" FORCE)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

project(lfs CXX)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(tests)

add_library(lfs SHARED
    lfs.cpp
)
