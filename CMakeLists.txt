cmake_minimum_required(VERSION 3.20)

project(GdIconMaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geode REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

setup_geode_mod(
    id "razzgd.gd_icon_maker"
)

target_sources(GdIconMaker PRIVATE ${SOURCES})
