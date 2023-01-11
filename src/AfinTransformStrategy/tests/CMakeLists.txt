cmake_minimum_required(VERSION 3.5)

project(test_afin VERSION 0.1 LANGUAGES CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_BUILD_TYPE Release)
include(CPack)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS )
find_package(Qt6 REQUIRED COMPONENTS Gui) 
find_package(Qt6 REQUIRED COMPONENTS OpenGL) 
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(GTest)



add_executable(test_afin
  afin_transform_tests.cc
  ../AfinTransformStrategy.cc
  ../AfinTransformStrategy.h
)

target_link_libraries(test_afin PRIVATE Qt6::Gui)
target_link_libraries(test_afin PRIVATE Qt6::OpenGL)
target_link_libraries(test_afin PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(test_afin PRIVATE Qt${QT_VERSION_MAJOR}::Core GTest::GTest GTest::Main)