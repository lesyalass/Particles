cmake_minimum_required(VERSION 3.2)     

project(PerfectGas CXX)  
          
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SOURCE_EXE PerfectGas.cpp)       

add_executable(main ${SOURCE_EXE})       

target_link_libraries(main sfml-graphics sfml-audio)