cmake_minimum_required(VERSION 3.5)

project(viewer VERSION 0.1 LANGUAGES CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")# -Wall -Werror -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)
find_package(Qt6 COMPONENTS Widgets OpenGL REQUIRED)

set(PROJECT_SOURCES
        ../Main.cpp
        ../Commands/Shell.cc
        ../Commands/MoveCommands.h
        ../Commands/RotateCommands.h
        ../Commands/VerticeCommands.h
        ../Commands/LineCommands.h
        ../Commands/ProgCommands.h
        ../Commands/AbstractCommand.h
        ../Commands/Shell.h
        ../OGLWidget/OGLWidget.h
        ../OGLWidget/OGLWidget.cc
        ../AfinTransformStrategy/AfinTransformStrategy.h
        ../AfinTransformStrategy/AfinTransformStrategy.cc
        ../BackFasade/BackFasade.cc
        ../BackFasade/BackFasade.h
        ../Controller/Controller.h
        ../Mediator/Mediator.h
        ../Mediator/AbstractMediator.h
        ../Helpers/Helpers.h
        ../Parser/Parser.h
        ../Parser/Parser.cc
        ../Viewer/Mainwindow.cc
        ../Viewer/Mainwindow.h
        ../Viewer/EventFilter.h
        ../Viewer/EventFilter.cc
        ../Viewer/Mainwindow.ui

        ../OGLWidget/Error.h
        ../OGLWidget/Error.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET viewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(viewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# target_include_directories(viewer PUBLIC ../viewer)
# target_include_directories(viewer PUBLIC ../Commands)
target_include_directories(viewer PUBLIC ../OGLWidget)
# target_include_directories(viewer PUBLIC ../.buttons)

target_link_libraries(viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(viewer PRIVATE Qt6::OpenGLWidgets)

set_target_properties(viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(viewer)
endif()
