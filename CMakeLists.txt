cmake_minimum_required(VERSION 3.13)

# 1. Links perfectly to your exact case-sensitive repository identity
project(GdIconMaker)

include(FetchContent)

FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com
    GIT_TAG main
)
FetchContent_MakeAvailable(Geode)

# 2. Tracks the precise case-sensitive output format 
add_geode_mod(
    ${PROJECT_NAME}
    RazzGd.GdIconMaker
    SOURCES src/main.cpp
)
