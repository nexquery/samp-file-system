project(file-system)

cmake_minimum_required(VERSION 3.1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
)


set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DSAMPGDK_AMALGAMATION)

add_samp_plugin(file-system
	amxplugin.cpp
	compilation-date.hpp
	file-system.def
	main.cpp
	natives.cpp
	natives.hpp
	plugin.h
	plugincommon.h
	precompiler.hpp
	sampgdk.cpp
	sampgdk.hpp
	service.cpp
	service.hpp
	slot-manager.cpp
	slot-manager.hpp
	utils.cpp
	utils.hpp
	version.hpp
)