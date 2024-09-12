cmake_minimum_required(VERSION 3.28)

project(test_cpu)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Pour Windows : empêcher le remplacement des paramètres du compilateur/éditeur de liens du projet parent
set(gtest_force_shared_crt SUR CACHE BOOL "" FORCE)
set(CTEST_VERBOSE TRUE)
set(CTEST_OUTPUT_ON_FAILURE TRUE)


file(GLOB_RECURSE SRC_LIST

	../src/*.h
	../src/*.hpp
	../src/*.c
	../src/*.cpp

)

add_library(test_cpu_lib STATIC ${SRC_LIST})

find_package(GTest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_cpu ${SRC_LIST})
target_link_libraries(test_cpu PUBLIC gtest_main )

add_test(NAME LDATests COMMAND test_cpu)
