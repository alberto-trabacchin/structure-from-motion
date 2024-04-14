cmake_minimum_required(VERSION 3.0)

project(
    "StructureFromMotion"
    VERSION 0.1.0
    LANGUAGES CXX
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(application src/application.cpp)

find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )

target_link_libraries( application ${OpenCV_LIBS} ${Boost_LIBRARIES} )