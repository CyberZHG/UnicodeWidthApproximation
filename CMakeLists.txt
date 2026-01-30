cmake_minimum_required(VERSION 4.0)
project(UnicodeWidthApproximation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(UNICODE_WIDTH_APPROXIMATION_ENABLE_STRICT "Use strict compile options" OFF)
option(UNICODE_WIDTH_APPROXIMATION_ENABLE_COVERAGE "Enable coverage reporting" OFF)
option(UNICODE_WIDTH_APPROXIMATION_ENABLE_TESTS "Build tests" OFF)
option(UNICODE_WIDTH_APPROXIMATION_BIND_PYTHON "Enable Python binding" OFF)
option(UNICODE_WIDTH_APPROXIMATION_BIND_ES "Enable ECMAScript binding" OFF)

if(APPLE)
    set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

if(UNICODE_WIDTH_APPROXIMATION_ENABLE_STRICT)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(
                -Wall
                -Wextra
                -Werror
                -Wpedantic
                -Wmissing-include-dirs
                -Wundef
                -Wredundant-decls
        )
    endif()
endif()

if(UNICODE_WIDTH_APPROXIMATION_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g -fno-elide-constructors -fno-default-inline)
        add_link_options(--coverage)
    endif()
endif()

include(FetchContent)

FetchContent_Declare(
        GraphemeClusterBreak
        GIT_REPOSITORY https://github.com/CyberZHG/GraphemeClusterBreak.git
        GIT_TAG v1.1.0
)
FetchContent_MakeAvailable(GraphemeClusterBreak)

add_library(UnicodeWidthApproximation STATIC
        include/unicode_width.h
        src/unicode_width.cpp
)

target_include_directories(UnicodeWidthApproximation
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(UnicodeWidthApproximation
        PUBLIC GraphemeClusterBreak
)

if(UNICODE_WIDTH_APPROXIMATION_ENABLE_TESTS)
    enable_testing()

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(runTests
            tests/main.cpp
            tests/test_width_properties.cpp
            tests/test_string_width.cpp
    )

    target_link_libraries(runTests
            PRIVATE UnicodeWidthApproximation
            PRIVATE gtest gtest_main
    )

    add_test(NAME UnicodeWidthApproximationTests COMMAND runTests)

endif()

if(UNICODE_WIDTH_APPROXIMATION_BIND_PYTHON)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v3.0
    )
    FetchContent_MakeAvailable(pybind11)

    pybind11_add_module(_core
            python/binding.cpp
    )
    target_link_libraries(_core
            PRIVATE UnicodeWidthApproximation
    )
    install(TARGETS _core
            LIBRARY DESTINATION unicode_width_approximation)
    install(FILES python/wrapper/__init__.py DESTINATION unicode_width_approximation)
endif()

if (UNICODE_WIDTH_APPROXIMATION_BIND_ES)
    add_executable(UnicodeWidthApproximationWASM
            wasm/binding.cpp)

    target_link_libraries(UnicodeWidthApproximationWASM
            PRIVATE UnicodeWidthApproximation
    )

    target_compile_options(UnicodeWidthApproximationWASM PRIVATE "-O3")

    set_target_properties(UnicodeWidthApproximationWASM PROPERTIES SUFFIX ".js")

    target_link_options(UnicodeWidthApproximationWASM PRIVATE
            "--bind"
            "-sMODULARIZE=1"
            "-sEXPORT_ES6=1"
            "-sEXPORT_NAME=UnicodeWidthApproximationWASMModule"
            "-sNO_DISABLE_EXCEPTION_CATCHING"
    )
endif ()
