cmake_minimum_required(VERSION 3.27)
project(EventDrivenSimulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)


add_executable(Scenario
        Main.cpp
        EoModel.cpp
        SimEngine.cpp
        Event.cpp
        Generator.cpp
        Transducer.cpp
        Product.cpp
        Machine.cpp
        AGV.cpp
        Position.cpp
        Storage.cpp
        EoModel.h
        SimEngine.h
        Event.h
        Generator.h
        Transducer.h
        Product.h
        Machine.h
        AGV.h
        Position.h
        Storage.h
)
