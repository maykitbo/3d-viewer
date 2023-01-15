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

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")# -Wall -Werror -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        ../main.cpp
        ../Commands/Commands.cc
        ../Commands/Moves.h
        ../Commands/Rotates.h
        ../Commands/Vertices.h
        ../Commands/Lines.h
        ../Commands/ProgCommands.h
        ../Commands/AbstractCommand.h
        ../Commands/CommandsQueue.h
        ../Commands/Commands.h
        ../Commands/settingscomm
        # ../Controller/Controller.cc
        ../Controller/Controller.h
        ../Fasade/Fasade.cc
        ../Fasade/UndoRedoFasade.cc
        ../Fasade/Fasade.h
        ../Helpers/Helpers.h
        ../Parser/Parser.h
        ../Parser/Parser.cc
        ../viewer/mainwindow.cc
        ../viewer/mainwindow.h
        ../viewer/EventFilter.h
        ../viewer/EventFilter.cc
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

target_include_directories(viewer PUBLIC ../viewer)
target_include_directories(viewer PUBLIC ../Commands)

target_link_libraries(viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
