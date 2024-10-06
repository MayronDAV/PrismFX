cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()
cmake_policy(SET CMP0072 NEW)

project(
	PrismFX
	LANGUAGES CXX C
)

#============================== SETUP =======================================

set(PROJECT_VERSION)
set(PROJECT_VERSION_MAJOR)
set(PROJECT_VERSION_MINOR)
set(CMAKE_CXX_STANDARD 20)
#============================================================================

#============================== PROJECT =====================================

set(GAME_LIBRARY ${PROJECT_NAME})
set(GAME_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/source")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/**.cpp")

set(THIRDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")

#OpenGL setup
find_package(OpenGL REQUIRED)
list(APPEND GAME_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
set(GAME_LIBRARIES ${OPENGL_gl_LIBRARY})
list(APPEND GAME_LIBRARIES ${OPENGL_glu_LIBRARY})

#GLFW setup
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${THIRDPARTY_DIR}/glfw")
list(APPEND GAME_LIBRARIES glfw)

# GLAD setup
add_subdirectory("${THIRDPARTY_DIR}/glad")
list(APPEND GAME_INCLUDE_DIRS ${GLAD_INCLUDE_DIRS})

# GLM setup
add_subdirectory("${THIRDPARTY_DIR}/glm")
list(APPEND GAME_LIBRARIES glm-header-only)

# SPDLOG setup
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory("${THIRDPARTY_DIR}/spdlog")
list(APPEND GAME_LIBRARIES spdlog)
#============================================================================

#============================== BUILD SETUP =================================

include_directories(${GAME_INCLUDE_DIRS})

if(MSVC)
    add_compile_options(/Wv:2)
elseif(UNIX)
    add_compile_options(-Wno-dll-interface)
endif()

add_library(${GAME_LIBRARY} SHARED ${SOURCES} ${GLAD_SOURCES})

target_precompile_headers(${GAME_LIBRARY} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/source/PrismFX/pfx_pch.h>")

target_compile_definitions(${GAME_LIBRARY} PRIVATE PFX_BUILD)
if(WIN32)
	target_compile_definitions(${GAME_LIBRARY} PRIVATE PFX_PLATFORM_WINDOWS)
elseif(UNIX)
	target_compile_definitions(${GAME_LIBRARY} PRIVATE PFX_PLATFORM_UNIX)
endif()

set_target_properties(${GAME_LIBRARY} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin"
)

target_link_libraries(${GAME_LIBRARY} ${GAME_LIBRARIES})
#============================================================================
