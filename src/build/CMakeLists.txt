cmake_minimum_required(VERSION 3.5)

project(viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)
find_package(Qt6 COMPONENTS Widgets OpenGL REQUIRED)




set(PROJECT_SOURCES
        ../main.cpp
        ../dscene/dscene.cpp
        ../dscene/dscene.h
        ../OGLWidget/OGLWidget.h
        ../OGLWidget/OGLWidget.cc
        ../AfinTransformStrategy/AfinTransformStrategy.h
        ../AfinTransformStrategy/AfinTransformStrategy.cc
        # ../Commands/Commands.cc
        ../Commands/Commands.h
        # ../Controller/Controller.cc
        ../Controller/Controller.h
        ../Fasade/Fasade.cc
        ../Fasade/Fasade.h
        ../Helpers/Helpers.h
        ../Parser/Parser.h
        ../Parser/Parser.cc
        ../viewer/mainwindow.cc
        ../viewer/mainwindow.h
        ../viewer/mainwindow.ui

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

target_include_directories(viewer PUBLIC ../OGLWidget)
target_include_directories(viewer PUBLIC ../dscene)

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
