cmake_minimum_required(VERSION 3.21)
project(Game LANGUAGES CXX VERSION 0.0.1)

set(SRCS "")

# Sources
file(GLOB_RECURSE SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

# Inlines
file(GLOB_RECURSE INLS_G "include/*.inl")
POCO_SOURCES_AUTO(SRCS ${INLS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.hpp")
POCO_HEADERS_AUTO(SRCS ${HDRS_G})

# Compile game libraries
FILE(GLOB libMakeFiles RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/*/CMakeLists.txt
)
foreach (f ${libMakeFiles})
    get_filename_component(dir ${f} DIRECTORY)
    add_subdirectory(${dir})
endforeach()

# Create static lib for invoking main game object
# from other target
add_library(${PROJECT_NAME} STATIC ${SRCS})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
                sfml-graphics
                sfml-audio
                sfml-network
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME    "${PROJECT_NAME}"
    SUFFIX         ""
    PREFIX         ""
    VERSION        "${PROJECT_VERSION}"
    PUBLIC_HEADER  "${HDRS_G}"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
