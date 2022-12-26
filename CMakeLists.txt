cmake_minimum_required(VERSION 3.21)
project(SSAG LANGUAGES CXX DESCRIPTION "Space ship adventure game")

set(VEXILE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
        set(DEFAULT_BUILD_TYPE "Debug")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
        EXECUTE_PROCESS(COMMAND
                ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
ENDIF()

include(PocoMacros.cmake)

set(SFML_BUILD_DOC TRUE)
set(SFML_BUILD_AUDIO TRUE)
set(SFML_BUILD_NETWORK TRUE)
set(SFML_BUILD_GRAPHICS TRUE)
set(SFML_BUILD_WINDOW TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)
set(BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${BINARY_DIR}/lib)

find_package(SFML 2.5 
        COMPONENTS system window graphics network audio REQUIRED)

# Build lib/*
# FILE(GLOB libMakeFiles RELATIVE
#         ${CMAKE_CURRENT_SOURCE_DIR}
#         ${CMAKE_CURRENT_SOURCE_DIR}/lib/*/CMakeLists.txt
#         )
# foreach (f ${libMakeFiles})
#         get_filename_component(dir ${f} DIRECTORY)
#         add_subdirectory(${dir})
#
#         # get_target_property(DEPS ${} LINK_LIBRARIES)
#         # foreach (DEP ${DEPS})
#         #         install(
#         #                 FILES $<TARGET_FILE:${DEP}>
#         #                 DESTINATION ${BINARY_DIR}/lib)
#         # endforeach()
# endforeach()

add_subdirectory(Game)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Game)
