cmake_minimum_required(VERSION 3.15.0)
project(RISK_Simulator LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.2.0
)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.13
)

FetchContent_MakeAvailable(fmt pybind11)

add_library(core core/src/country.cpp core/src/region.cpp core/src/simulation.cpp)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
target_link_libraries(core PUBLIC fmt::fmt)


#add_executable(RISK_sim main.cpp)
#target_link_libraries(RISK_sim PRIVATE core PUBLIC fmt::fmt)
#target_include_directories(RISK_sim PRIVATE ${core_include_dir})

pybind11_add_module(RISK_pycore core/src/bind_py.cpp)
target_link_libraries(RISK_pycore PRIVATE core)
target_include_directories(RISK_pycore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/include)