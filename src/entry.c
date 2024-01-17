/*
    This file is a part of yoyo-rpc. (https://github.com/yoyolick/yoyo-rpc)
    Copyright (C) 2024  Ryan Zmuda

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <yoyoengine/yoyoengine.h>
#include <yoyoengine/yoyo_trick_boilerplate.h>

#include "yoyo-rpc.h"

void yoyo_trick_init(){
    ye_register_trick((struct ye_trick_node){
        .name = "yoyo-rpc",
        .author = "Ryan Zmuda",
        .description = "Provides a simple RPC wrapper around the discord games SDK to yoyoengine.",
        .version = "1.0.0",
        .on_unload = YYRPC_on_unload,
        .on_update = YYRPC_on_update,
        .lua_bind = YYRPC_lua_bind
    });
}