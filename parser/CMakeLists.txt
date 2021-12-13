cmake_minimum_required(VERSION 3.16.3)
project(parser VERSION 1.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCE_FILES utils.cpp parser.cpp)
add_library(libparser STATIC ${LIB_SOURCE_FILES})

add_executable(main main.cpp)
target_link_libraries(main libparser)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests.cpp utils.cpp parser.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} libparser pthread)