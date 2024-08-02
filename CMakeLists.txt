cmake_minimum_required(VERSION 3.5)

project(satellites VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
        ${CMAKE_SOURCE_DIR}/src/mainwindow.h
        ${CMAKE_SOURCE_DIR}/src/mainwindow.ui
)

qt_add_executable(satellites
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${CMAKE_SOURCE_DIR}/src/infowindow.h ${CMAKE_SOURCE_DIR}/src/infowindow.cpp ${CMAKE_SOURCE_DIR}/src/infowindow.ui
    ${CMAKE_SOURCE_DIR}/src/satellite.h ${CMAKE_SOURCE_DIR}/src/satellite.cpp
    ${CMAKE_SOURCE_DIR}/src/tlereader.h ${CMAKE_SOURCE_DIR}/src/tlereader.cpp
)

target_link_libraries(satellites PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(satellites PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS satellites
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(satellites)
