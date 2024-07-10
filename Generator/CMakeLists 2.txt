# cmake_minimum_required(VERSION 3.1.0)
# project(Simulator)

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Export)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Export)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Export)

# include_directories(.)


# add_executable(Generator
#         main.cpp
#         # Product.h
#         # Product.cpp
#         # Process_rule.h
#         # Process_rule.cpp
#         # Machine.h
#         # Machine.cpp
#         Cell.h
#         Cell.cpp
#         AGV.h
#         AGV.cpp
#         Map.h
#         Map.cpp
#         Part.h
#         Part.cpp
        
# )

cmake_minimum_required(VERSION 3.15)
project(Simulator)

set(CMAKE_CXX_STANDARD 17)

# Set the build output location to a common directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Export)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Export)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Export)

include_directories(.)

# Add OpenXLSX as a subdirectory
add_subdirectory(OpenXLSX)

# Add the executable and link OpenXLSX
add_executable(Generator
    main.cpp
    Cell.h
    Cell.cpp
    AGV.h
    AGV.cpp
    Map.h
    Map.cpp
    Part.h
    Part.cpp
)

target_link_libraries(Generator OpenXLSX::OpenXLSX)
