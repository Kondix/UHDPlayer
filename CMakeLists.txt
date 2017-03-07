cmake_minimum_required(VERSION 3.6)
project(UHDPlayer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DisplayHandler.cpp DisplayHandler.h Controler.cpp Controler.h FileOpener.h RawDataHandler.cpp RawDataHandler.h Types.h Callbacks.h ImemOptionsHandler.h)
set(VLC_LIB /usr/lib/libvlc.so)
add_executable(UHDPlayer ${SOURCE_FILES})
LINK_DIRECTORIES(${VLC_LIB})
TARGET_LINK_LIBRARIES(UHDPlayer libvlc.so)