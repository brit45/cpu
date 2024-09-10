cmake_minimum_required(VERSION 3.28)

project("Cpu")

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set (SRC ${CMAKE_SOURCE_DIR}/src )
set (TESTS ${CMAKE_SOURCE_DIR}/Tests )


file(GLOB_RECURSE SRC_LIST 
    ${SRC}/**.h
    ${SRC}/**.hpp
    ${SRC}/**.inl
    ${SRC}/**.cpp
)

add_library(Cpulib STATIC ${SRC_LIST})

add_executable(Cpu ${SRC_LIST})
target_link_libraries(Cpu)

add_subdirectory(${TESTS})
