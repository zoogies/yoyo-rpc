# This file is a part of yoyo-rpc. (https://github.com/yoyolick/yoyo-rpc)
# Copyright (C) 2024  Ryan Zmuda
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.22.1)

project(yoyo-rpc)

set(SOURCES
    src/entry.c
    src/yoyo-rpc.c
)

include_directories(
    ./include/
    ./src/
)

add_library(yoyo-rpc SHARED ${SOURCES})

if (UNIX)
    target_link_libraries(yoyo-rpc ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/libdiscord_game_sdk.so)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/libdiscord_game_sdk.so DESTINATION ${YOYO_TRICK_BUILD_DIR})
elseif (WIN32)
    target_link_libraries(yoyo-rpc ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/discord_game_sdk.dll)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libdiscord_game_sdk.dll DESTINATION ${YOYO_TRICK_BUILD_DIR})
else()
    message(FATAL_ERROR "Unsupported platform when building yoyo-rpc")
endif()

set_target_properties(yoyo-rpc PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${YOYO_TRICK_BUILD_DIR})
set_target_properties(yoyo-rpc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${YOYO_TRICK_BUILD_DIR})