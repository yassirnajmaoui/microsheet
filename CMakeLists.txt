cmake_minimum_required(VERSION 3.5)

project(microsheet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)


set(PROJECT_SOURCES
    main.cpp
    spreadsheet.cpp spreadsheet.hpp
    spreadsheetdelegate.cpp spreadsheetdelegate.hpp
    spreadsheetitem.cpp spreadsheetitem.hpp
    console/QConsoleIODevice.cpp console/QConsoleIODevice.h console/QConsoleWidget.cpp console/QConsoleWidget.h
    util.hpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(microsheet MANUAL_FINALIZATION ${PROJECT_SOURCES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET microsheet APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
	add_executable(microsheet ${PROJECT_SOURCES})
endif()

target_link_libraries(microsheet PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(microsheet PRIVATE pybind11::embed)

set_target_properties(microsheet PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER microsheet.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(microsheet)
endif()




