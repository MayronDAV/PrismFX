cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()
cmake_policy(SET CMP0072 NEW)

project(
	Sandbox
	LANGUAGES CXX C
)

#============================== SETUP =======================================

set(PROJECT_VERSION)
set(PROJECT_VERSION_MAJOR)
set(PROJECT_VERSION_MINOR)
set(CMAKE_CXX_STANDARD 20)
#============================================================================

#============================== PROJECT =====================================

set(PRISMFX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../PrismFX")

file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/**.cpp")

#============================================================================

#============================== BUILD SETUP =================================

include_directories(${PRISMFX_DIR}/source)

link_directories(${PRISMFX_DIR}/Bin)

add_executable(${PROJECT_NAME} ${SANDBOX_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")

target_link_libraries(${PROJECT_NAME} PrismFX)

#============================================================================

#========================== COPY SHARED LIBRARY =============================

set(SANDBOX_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Bin/${CMAKE_BUILD_TYPE}")

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${PRISMFX_DIR}/Bin/${CMAKE_BUILD_TYPE}/PrismFX.dll"
		"${SANDBOX_BIN_DIR}/PrismFX.dll"
	)
elseif(UNIX)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${PRISMFX_DIR}/Bin/${CMAKE_BUILD_TYPE}/libPrismFX.so"
		"${SANDBOX_BIN_DIR}/libPrismFX.so"
	)
endif()

#============================================================================