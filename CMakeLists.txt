cmake_minimum_required(VERSION 3.20)

project(GdIconMaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geode REQUIRED)

# 1. Find all C++ files in the src folder automatically
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 2. Setup the mod (Looks for mod.json in the SAME folder as this file)
setup_geode_mod(
    id "razzgd.gd_icon_maker"
)

# 3. Add the sources we found to the mod
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
