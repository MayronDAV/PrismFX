cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

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

add_subdirectory(PrismFX)

add_subdirectory(Sandbox)
