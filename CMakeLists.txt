cmake_minimum_required(VERSION 3.20)
project(SortingLabs VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(SORTING_RUN_TESTS_AFTER_BUILD "Run all Catch2 tests after linking" ON)

function(add_sort_library directory name)
    add_library(${name} STATIC ${directory}/src/${name}.cpp ${directory}/include/${name}.h)
    target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${directory}/include)
    if(MSVC)
        target_compile_options(${name} PRIVATE /W4 /permissive- /utf-8)
    else()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    set_property(TARGET ${name} PROPERTY FOLDER "SortingLibraries")
endfunction()
add_sort_library(sorting insertion_sort)
add_sort_library(sorting selection_sort)
add_sort_library(sorting exchange_sort)
add_sort_library(sorting bubble_sort)
add_sort_library(sorting optimized_bubble_sort)
add_sort_library(enhanced_sorting binary_insertion_sort)
add_sort_library(enhanced_sorting shaker_sort)
add_sort_library(enhanced_sorting shell_sort)
add_sort_library(enhanced_sorting quick_sort)
add_sort_library(external_sorting two_phase_merge_sort)
add_sort_library(external_sorting one_phase_merge_sort)
add_sort_library(external_sorting natural_merge_sort)

set(SORTING_LIBRARIES
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
add_custom_target(SortingLibraries DEPENDS ${SORTING_LIBRARIES})

enable_testing()
set(TEST_SOURCES tests/main.cpp tests/test_helpers.h tests/test_file_support.cpp tests/test_optimizations.cpp
    tests/test_insertion_sort.cpp
    tests/test_selection_sort.cpp
    tests/test_exchange_sort.cpp
    tests/test_bubble_sort.cpp
    tests/test_optimized_bubble_sort.cpp
    tests/test_binary_insertion_sort.cpp
    tests/test_shaker_sort.cpp
    tests/test_shell_sort.cpp
    tests/test_quick_sort.cpp
    tests/test_two_phase_merge_sort.cpp
    tests/test_one_phase_merge_sort.cpp
    tests/test_natural_merge_sort.cpp
)
add_executable(SortingTests ${TEST_SOURCES})
target_include_directories(SortingTests PRIVATE third_party tests)
target_link_libraries(SortingTests PRIVATE ${SORTING_LIBRARIES})
if(MSVC)
    target_compile_options(SortingTests PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(SortingTests PRIVATE -Wall -Wextra -Wpedantic)
endif()
foreach(lab RANGE 1 4)
    add_test(NAME lab${lab} COMMAND SortingTests "[lab${lab}]")
endforeach()
if(SORTING_RUN_TESTS_AFTER_BUILD)
    add_custom_command(TARGET SortingTests POST_BUILD
        COMMAND $<TARGET_FILE:SortingTests>
        COMMENT "Running all Catch2 unit tests" VERBATIM)
endif()
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT SortingTests)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
