cmake_minimum_required(VERSION 3.13)

# Perfectly mapped to match your exact case tracking rules
project(GdIconMaker)

include(FetchContent)

FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com
    GIT_TAG main
)
FetchContent_MakeAvailable(Geode)

add_geode_mod(
    ${PROJECT_NAME}
    RazzGd.GdIconMaker
    SOURCES src/main.cpp
)
