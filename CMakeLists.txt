cmake_minimum_required(VERSION 3.5.1)
project(clipaint)

option(BUILD_WITH_DEBUG "Adds debug code" OFF)
option(BUILD_DEBUG "Build a debug release" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(${BUILD_DEBUG})
        set(CMAKE_BUILD_TYPE Debug)

else()
        set(CMAKE_BUILD_TYPE Release)
endif()


add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#add_subdirectory("${PROJECT_SOURCE_DIR}/src")
include_directories("include")

if(${BUILD_WITH_DEBUG})
	add_compile_definitions(WDEBUG_CODE)
endif()


#libraries... added manually. Sorry, that's life.
add_library(terminal STATIC IMPORTED)
add_library(utf8tools STATIC IMPORTED)
add_library(tools STATIC IMPORTED)

set_target_properties(terminal PROPERTIES IMPORTED_LOCATION /usr/local/lib/libterminal-tools.a)
set_target_properties(utf8tools PROPERTIES	IMPORTED_LOCATION /usr/local/lib/libutf8tools.a)
set_target_properties(tools PROPERTIES	IMPORTED_LOCATION /usr/local/lib/libtools.a)

set(SRCDIR src)
set(SOURCE
	${SRCDIR}/video/window.cpp
	${SRCDIR}/input/input.cpp
	${SRCDIR}/app/driver.cpp
	${SRCDIR}/app/canvas.cpp
	${SRCDIR}/app/colors.cpp
)

add_executable(clipaint src/main.cpp ${SOURCE})
target_link_libraries(clipaint terminal utf8tools tools)
