cmake_minimum_required(VERSION 3.5)
project(UHDPlayer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

find_package(Qt5Widgets)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(GUI_Srcs
        adminpanel.cpp
        adminpanel.ui
        mainwindow.cpp
        mainwindow.ui
        userpanel.cpp
        userpanel.ui
        videopanel.cpp
        videopanel.ui
        )


set(SOURCE_FILES main.cpp DisplayHandler.cpp DisplayHandler.h Controler.cpp Controler.h FileOpener.h RawDataHandler.cpp RawDataHandler.h Types.h Callbacks.h
        ImemOptionsHandler.h ThreadsHandler.cpp ThreadsHandler.h ${GUI_Srcs})
set(VLC_LIB /usr/lib/libvlc.so)
add_executable(UHDPlayer ${SOURCE_FILES})
LINK_DIRECTORIES(${VLC_LIB})
TARGET_LINK_LIBRARIES(UHDPlayer libvlc.so -lpthread -lm Qt5::Widgets Qt5::Core VLCQtCore VLCQtQml VLCQtWidgets)