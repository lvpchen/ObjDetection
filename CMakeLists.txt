cmake_minimum_required (VERSION 2.6)
project (ObjDetection)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ObjDetection main.cpp)
target_link_libraries(ObjDetection ${OpenCV_LIBS})
target_compile_features(ObjDetection PRIVATE cxx_range_for)
