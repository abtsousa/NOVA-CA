cmake_minimum_required(VERSION 3.24)
project(AC)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        *.h
        *.c
        *.s
        )

add_executable(ClionProject ${SOURCE_FILES} ${SOURCES})