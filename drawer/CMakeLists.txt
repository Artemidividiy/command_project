cmake_minimum_required(VERSION 3.0.0)
project(drawer VERSION 0.1.0)

include(CTest)
enable_testing()

SET(SOURCES
    2dDecart.cpp
    3dDecart.cpp
    cylinder.cpp
    drawer.cpp
    polar.cpp
    second_dim_drawer.cpp
    spherical.cpp
    third_dim_drawer.cpp
)

SET(HEADERS
    2dDecart.h
    3dDecart.h
    cylinder.h
    drawer.h
    polar.h
    second_dim_drawer.h
    spherical.h
    third_dim_drawer.h
)

add_library(drawer main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
