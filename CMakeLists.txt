cmake_minimum_required(VERSION 3.15.0)
project(R.I.S.K. Simulator LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.2.0
)

FetchContent_MakeAvailable(fmt)

add_library(core core/src/country.cpp)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)

add_subdirectory(asm)
add_subdirectory(memory)

add_library(sim SHARED)
target_link_libraries(sim PRIVATE asm core memory PUBLIC fmt::fmt)
#target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
#target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/memory)
set_target_properties(sim PROPERTIES POSITION_INDEPENDENT_CODE ON OUTPUT_NAME "sim")

add_executable(RISK_sim main.cpp)
target_link_libraries(RISK_sim PRIVATE sim)