cmake_minimum_required(VERSION 3.10)

project(cpp-bench CXX)

include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)
conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD
    missing
 
)

add_executable(${PROJECT_NAME} src/bench.cpp)
conan_target_link_libraries(${PROJECT_NAME})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -O3
        -march=native
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc
        /O2
        /W4
        /WX
    )
endif()
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_custom_target(
    bench $<TARGET_FILE:${PROJECT_NAME}> --benchmark_repetitions=10 --benchmark_display_aggregates_only=true
    DEPENDS ${PROJECT_NAME}
)
