cmake_minimum_required(VERSION 3.20)
project(DuplicateSearch CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(FetchContent)
find_package(OpenSSL 3.0 REQUIRED COMPONENTS Crypto)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_library(imgsim 
    src/hash.cpp 
    src/search.cpp
    src/sha256.cpp
)
target_include_directories(imgsim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(imgsim PRIVATE OpenSSL::Crypto)
add_executable(imgsim_smoke src/main.cpp)
target_link_libraries(imgsim_smoke PRIVATE imgsim OpenSSL::Crypto)

enable_testing()

add_executable(imgsim_tests
    tests/hash_test.cpp
    tests/search_test.cpp
    tests/sha256_test.cpp
)

target_link_libraries(imgsim_tests PRIVATE
    imgsim
    GTest::gtest_main
    OpenSSL::Crypto
)

include(GoogleTest)
gtest_discover_tests(imgsim_tests)
