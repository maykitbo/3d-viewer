cmake_minimum_required(VERSION 3.5)

project(commands_test VERSION 0.1 LANGUAGES CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lgtest_main -lgtest -lpthread")

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
        ../test.cc
        ../test.h
        ../test_fasade.h
        ../../../Commands/Commands.cc
        ../../../Commands/Moves.h
        ../../../Commands/Rotates.h
        ../../../Commands/Vertices.h
        ../../../Commands/Lines.h
        ../../../Commands/ProgCommands.h
        ../../../Commands/AbstractCommand.h
        ../../../Commands/CommandsQueue.h
        ../../../Commands/Commands.h
        ../../../Controller/Controller.h
        ../../../Mediator/Mediator.h
        ../../../Mediator/AbstractMediator.h
)




# target_link_libraries(
#   test
#   GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(test)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(commands_test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()


target_link_libraries(commands_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

