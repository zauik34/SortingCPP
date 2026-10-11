cmake_minimum_required(VERSION 3.20)
project(SortingCPP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    add_compile_options(/utf-8)
endif()

# При сборке через CMake каждый алгоритм — отдельная библиотека.
set(ALGORITHMS
    insertion_sort
    selection_sort
    exchange_sort
    bubble_sort
    optimized_bubble_sort
    binary_insertion_sort
    shaker_sort
    shell_sort
    quick_sort
    two_phase_merge_sort
    one_phase_merge_sort
    natural_merge_sort
)
foreach(name IN LISTS ALGORITHMS)
    add_library(${name} STATIC Sem1/${name}.cpp Sem1/${name}.h)
    target_include_directories(${name} PUBLIC Sem1)
endforeach()

add_executable(Test
    Test/Test.cpp
    Test/test_files.cpp
    Test/test_insertion_sort.cpp
    Test/test_selection_sort.cpp
    Test/test_exchange_sort.cpp
    Test/test_bubble_sort.cpp
    Test/test_optimized_bubble_sort.cpp
    Test/test_binary_insertion_sort.cpp
    Test/test_shaker_sort.cpp
    Test/test_shell_sort.cpp
    Test/test_quick_sort.cpp
    Test/test_two_phase_merge_sort.cpp
    Test/test_one_phase_merge_sort.cpp
    Test/test_natural_merge_sort.cpp
)
target_include_directories(Test PRIVATE . Sem1)
target_link_libraries(Test PRIVATE ${ALGORITHMS})
add_custom_command(TARGET Test POST_BUILD COMMAND $<TARGET_FILE:Test> VERBATIM)
enable_testing()
foreach(lab RANGE 1 4)
    add_test(NAME lab${lab} COMMAND Test "[lab${lab}]")
endforeach()
