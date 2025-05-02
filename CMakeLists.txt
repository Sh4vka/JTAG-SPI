cmake_minimum_required(VERSION 3.10)
project(JTAG_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/Include)

add_executable(a.out
    main.cpp
    Include/JTAG.cpp
    Include/SPI.cpp
    Include/Signal.cpp
)

