cmake_minimum_required(VERSION 3.2)     

project(PerfectGas CXX)  
          
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SOURCE_EXE PerfectGas.cpp)       

set(SOURCE_LIB MainWindow.cpp MainWindow.h Model.cpp Model.h Geom.h)            

add_library(foo STATIC ${SOURCE_LIB}) 

set_target_properties(foo PROPERTIES LINKER_LANGUAGE CXX)

add_executable(main ${SOURCE_EXE})       

target_link_libraries(main foo)  

target_link_libraries(main sfml-graphics sfml-audio)