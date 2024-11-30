cmake_minimum_required(VERSION 3.24)
project(SIMRApp VERSION 0.1)

set(CMAKE_C_STANDARD 99)


include_directories(include)
include_directories(resources)
include_directories(interpreter/include)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

SET(DEBUG_FLAGS "_DEBUG _WINDOWS")
SET(CMAKE_CXX_FLAGS  "${CMAKE_C_FLAGS} ${DEBUG_FLAGS}")


add_executable(${CMAKE_PROJECT_NAME} WIN32
	src/app.c
	src/console.c
	src/goal.c
	src/hero.c
	src/map.c
	src/SIMPRApp.c
	interpreter/src/interpreter.c
)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR dep/CSFML/lib/cmake/SFML)
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
include_directories(dep/CSFML/include)

# find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
# link_directories (dep/CSFML/lib/gcc)

target_link_libraries(${CMAKE_PROJECT_NAME} 
	${CMAKE_SOURCE_DIR}/dep/CSFML/lib/gcc/libcsfml-graphics.a
	${CMAKE_SOURCE_DIR}/dep/CSFML/lib/gcc/libcsfml-window.a
	${CMAKE_SOURCE_DIR}/dep/CSFML/lib/gcc/libcsfml-system.a
)

# set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
# target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -mwindows)

target_compile_options(
  ${CMAKE_PROJECT_NAME} PRIVATE -municode -mwindows
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ./resources/SIMPRApp.rc)