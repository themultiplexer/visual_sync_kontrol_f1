cmake_minimum_required(VERSION 3.5)
project(traktor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(HIDAPI_LIBRARY
	NAMES hidapi hidapi-libusb)

find_path(HIDAPI_INCLUDE_DIR
	NAMES hidapi.h
	PATH_SUFFIXES
	hidapi)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(HIDAPI
	DEFAULT_MSG
	HIDAPI_LIBRARY
	HIDAPI_INCLUDE_DIR)


add_compile_definitions(_USE_MATH_DEFINES)
add_executable(traktor main.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${HIDAPI_INCLUDE_DIR})

target_link_libraries(traktor ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OpenCV_LIBS} ${FREETYPE_LIBRARIES} ${HIDAPI_LIBRARY})
