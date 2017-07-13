cmake_minimum_required(VERSION 2.8)
project(SFGE)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

include_directories(include ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SFGE_SRC src/*.cpp include/*.h)

#SFML 
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
set(SFML_BUILD_EXAMPLES FALSE)
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include)
LIST(APPEND SFGE_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
  sfml-audio
  sfml-network)

#SFML Imgui
set(SFML_IMGUI ${EXTERNAL_DIR}/imgui-sfml/)
set(IMGUI_ROOT ${EXTERNAL_DIR}/imgui/)

set(SFML_ROOT ${EXTERNAL_DIR}/SFML/)
add_subdirectory(${SFML_IMGUI})
include_directories(${IMGUI_ROOT} ${SFML_IMGUI})
LIST(APPEND SFGE_LIBRARIES
	imgui-sfml)


#BOX2D
set(BOX2D_DIR ${EXTERNAL_DIR}/Box2D)

SET(BOX2D_INSTALL ON CACHE INTERNAL "")
SET(BOX2D_BUILD_STATIC ON  CACHE INTERNAL "")

add_subdirectory(${BOX2D_DIR})
include_directories(${BOX2D_DIR}/Box2D/)
LIST(APPEND SFGE_LIBRARIES
	Box2D)

LIST(APPEND SFGE_LIBRARIES
	Box2D)

#JSON
set(JSON_DIR ${EXTERNAL_DIR}/json/)
add_subdirectory(${JSON_DIR})
include_directories(${JSON_DIR}/src/)
LIST(APPEND SFGE_LIBRARIES
	nlohmann_json)

#PYTHON
IF(NOT WIN32)
	add_definitions(-Wall -Wextra -pedantic -std=c++11)

	IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
		add_definitions(-g -O0)
	ELSE()
		add_definitions(-O3)
	ENDIF()

	LIST(APPEND SFGE_LIBRARIES resolv)
ELSE()
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()


find_package(PythonLibs 3 EXACT REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})

LIST(APPEND SFGE_LIBRARIES ${PYTHON_LIBRARY})

#PYBIND11
set(PYBIND11_DIR ${EXTERNAL_DIR}/pybind11/)
add_subdirectory(${PYBIND11_DIR})
include_directories(${PYBIND11_DIR})
LIST(APPEND SFGE_LIBRARIES
  pybind11)

add_executable(SFGE ${SFGE_SRC})

target_link_libraries(SFGE ${SFGE_LIBRARIES})
