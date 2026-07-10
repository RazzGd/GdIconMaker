cmake_minimum_required(VERSION 3.13)

# Perfectly mapped to match your exact case tracking rules
project(GdIconMaker)

# This single line finds the Geode SDK headers that the runner downloads for you
find_package(Geode REQUIRED)

# Tracks the precise case-sensitive output format 
add_geode_mod(
    ${PROJECT_NAME}
    RazzGd.GdIconMaker
    SOURCES src/main.cpp
)
