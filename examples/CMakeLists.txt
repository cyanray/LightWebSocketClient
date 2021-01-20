cmake_minimum_required (VERSION 3.8)

macro(api_exe target)
    add_executable(${target} ${target}.cpp)
    target_link_libraries(${target} PRIVATE LightWSClient)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${target} PRIVATE pthread)
    endif()
endmacro()

api_exe(first)