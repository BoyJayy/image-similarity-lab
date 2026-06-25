cmake_minimum_required(VERSION 3.20)
project(DuplicateSearch CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(imgsim src/hash.cpp src/search.cpp)
target_include_directories(imgsim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(imgsim_smoke src/main.cpp)
target_link_libraries(imgsim_smoke PRIVATE imgsim)
