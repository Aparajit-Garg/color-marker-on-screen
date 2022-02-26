cmake_minimum_required(VERSION 3.16)
project(color-marker-on-screen)

set(CMAKE_CXX_STANDARD 14)

# opencv integration
find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")


if(APPLE)
    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(color-marker-on-screen ${OpenCV_LIBS})
endif()