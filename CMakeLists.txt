cmake_minimum_required (VERSION 3.8)

project ("LightWSClient")

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./src SRCS)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

option(LightWSClient_Build_Examples "Build examples" OFF)
if(LightWSClient_Build_Examples)
    add_subdirectory(examples)
endif(LightWSClient_Build_Examples)
