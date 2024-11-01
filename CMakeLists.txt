cmake_minimum_required(VERSION 3.16)

project(strafe-helper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/daffa/game/Qt/6.8.0/mingw_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        src/app.cpp
        src/app.h
        src/app.ui
        resources.qrc
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(strafe-helper
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    add_executable(strafe-helper ${PROJECT_SOURCES})
endif()

target_link_libraries(strafe-helper PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.strafe-helper)
endif()

set_target_properties(strafe-helper PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

include(GNUInstallDirs)
install(TARGETS strafe-helper
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(strafe-helper)
endif()
