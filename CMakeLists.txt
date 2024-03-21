cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp
        database_templates.cpp
        database.cpp
        application.h
        application.cpp
        trip.cpp
        string_helper.cpp
        date.cpp
        vehicle.cpp
        users.cpp
        users.cpp
        what.cpp
        what.h)
