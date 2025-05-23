cmake_minimum_required(VERSION 3.19)

project(MDIWindow VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/resource/*.qrc"
)
file(GLOB_RECURSE UI_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
# message(STATUS "Variable name CMAKE_CURRENT_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "Variable name PROJECT_SOURECS: ${PROJECT_SOURCES}")

set(INCLUDE_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build/MDIWindow_autogen/include")

qt_add_executable(MDIWindow
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
qt6_add_ui(MDIWindow ${INCLUDE_PREFIX} SOURCES ${UI_FILES})

target_link_libraries(MDIWindow PRIVATE Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(MDIWindow PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MDIWindow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MDIWindow)
endif()
