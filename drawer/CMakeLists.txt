cmake_minimum_required(VERSION 3.16.3)
project(drawer VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIB_SOURCE_FILES drawer.cpp 2dDecart.cpp 3dDecart.cpp cylinder.cpp polar.cpp second_dim_drawer.cpp spherical.cpp third_dim_drawer.cpp)
add_library(drawer STATIC ${LIB_SOURCE_FILES})
target_link_libraries(drawer)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests.cpp LIB_SOURCE_FILES)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

