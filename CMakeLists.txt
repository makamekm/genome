cmake_minimum_required( VERSION 3.0 )

PROJECT(genome CXX)

set(CMAKE_MAJOR_VERSION "0")
set(CMAKE_MINOR_VERSION "0")
set(CMAKE_PATCH_VERSION "0")
set(CMAKE_VERSION_STRING "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")

find_package( OpenGL REQUIRED )

include_directories( "glfw/include" )
include_directories( "glm/glm" )
include_directories( "Vulkan-Headers/include" )

IF (APPLE)
    link_directories($ENV{VULKAN_SDK}/lib)
    include_directories($ENV{VULKAN_SDK}/include)
ENDIF()

include_directories("imgui")
include_directories("imgui/examples")
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( BUILD_EXAMPLES OFF CACHE BOOL  "RCCpp libsonly" )

add_subdirectory( glfw )

if($ENV{DEVELOPMENT_MODE})
    add_definitions(-DDEVELOPMENT_MODE)
endif()

if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wno-deprecated-declarations" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()
     
file(GLOB SRC_VENDOR_FILES
    ${PROJECT_SOURCE_DIR}/imgui/*.cpp
    ${PROJECT_SOURCE_DIR}/imgui/*.h
)

set( SRC_VENDOR_IMGUI_FILES
     imgui/examples/imgui_impl_glfw.h
     imgui/examples/imgui_impl_glfw.cpp
     imgui/examples/imgui_impl_opengl2.h
     imgui/examples/imgui_impl_opengl2.cpp
)

set( MAIN_FILE
     main.cpp
)
     
file(GLOB SRC_COMPONENTS_FILES
    ${PROJECT_SOURCE_DIR}/components/**/**/*.cpp
    ${PROJECT_SOURCE_DIR}/components/**/**/*.h
    ${PROJECT_SOURCE_DIR}/components/**/*.cpp
    ${PROJECT_SOURCE_DIR}/components/**/*.h
    ${PROJECT_SOURCE_DIR}/components/*.cpp
    ${PROJECT_SOURCE_DIR}/components/*.h
)

if($ENV{DEVELOPMENT_MODE})
    file(GLOB DEVELOPMENT_SRC_COMPONENTS_FILES
        ${PROJECT_SOURCE_DIR}/development/**/**/*.cpp
        ${PROJECT_SOURCE_DIR}/development/**/**/*.h
        ${PROJECT_SOURCE_DIR}/development/**/*.cpp
        ${PROJECT_SOURCE_DIR}/development/**/*.h
        ${PROJECT_SOURCE_DIR}/development/*.cpp
        ${PROJECT_SOURCE_DIR}/development/*.h
    )
endif()

file(GLOB PRODUCTION_SRC_COMPONENTS_FILES
    ${PROJECT_SOURCE_DIR}/production/**/**/*.cpp
    ${PROJECT_SOURCE_DIR}/production/**/**/*.h
    ${PROJECT_SOURCE_DIR}/production/**/*.cpp
    ${PROJECT_SOURCE_DIR}/production/**/*.h
    ${PROJECT_SOURCE_DIR}/production/*.cpp
    ${PROJECT_SOURCE_DIR}/production/*.h
)

add_executable( genome ${SRC_VENDOR_FILES} ${SRC_VENDOR_IMGUI_FILES} ${SRC_COMPONENTS_FILES} ${PRODUCTION_SRC_COMPONENTS_FILES} ${DEVELOPMENT_SRC_COMPONENTS_FILES} ${MAIN_FILE} )

add_custom_command(
    TARGET genome POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/resources/verdana.ttf
            ${CMAKE_CURRENT_BINARY_DIR}/resources/verdana.ttf
)

target_link_libraries( genome ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} )

if( MSVC )
    if( ${CMAKE_VERSION} VERSION_LESS "3.6.0" )
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'genome' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT genome )
    endif()
endif()
