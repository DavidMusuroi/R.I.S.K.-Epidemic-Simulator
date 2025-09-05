cmake_minimum_required(VERSION 3.15.0)
project(R.I.S.K_Simulator LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.2.0
)

FetchContent_MakeAvailable(fmt)

add_library(core core/src/country.cpp core/src/region.cpp)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)


add_executable(RISK_sim main.cpp)
target_link_libraries(RISK_sim PRIVATE core PUBLIC fmt::fmt)
target_include_directories(RISK_sim PRIVATE ${core_include_dir})

configure_file(${CMAKE_SOURCE_DIR}/data/countries.csv ${CMAKE_BINARY_DIR}/countries.csv COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/RO_counties.csv ${CMAKE_BINARY_DIR}/RO_counties.csv COPYONLY)