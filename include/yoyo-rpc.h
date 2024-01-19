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

#include <yoyoengine/export.h>

#include "discord_game_sdk.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <string.h>
#endif

// defines the application context
struct Application {
    struct IDiscordCore* core;
    struct IDiscordActivityManager* activities;
};

/**
 * @brief Destroys the RPC context
 */
void YYRPC_on_unload();

/**
 * @brief Runs the RPC callbacks to discord
 */
void YYRPC_on_update();

/**
 * @brief Initializes the RPC context with your client ID
 * 
 * @param client_id The client ID of your application (obtained through the discord developer portal)
 * @return true Success
 * @return false Failure
 */
YOYO_EXPORT bool YYRPC_initialize(DiscordClientId client_id);

/**
 * @brief Take in a full struct DiscordActivity and set it as the current activity
 * 
 * @param activity 
 * @return true 
 * @return false 
 * 
 * For this function, you need to have fully constructed a struct DiscordActivity. Make sure to memset it to 0 first.
 */
YOYO_EXPORT bool YYRPC_set_activity_complex(struct DiscordActivity activity);

/**
 * @brief Set the activity with a few parameters
 * 
 * @param details The details of the activity
 * @param state The state of the activity
 * @param large_image The large image key
 * @param large_text The large image text
*/
YOYO_EXPORT bool YYRPC_set_activity(char* details, char* state, char* large_image, char* large_text);

/* Lua */

/**
 * @brief The lua binding for YYRPC_initialize
 * 
 * @param L The lua state
 */
int YYRPC_lua_initialize(lua_State* L);

/**
 * @brief The lua binding for YYRPC_set_activity
 * 
 * @param L The lua state 
 */
int YYRPC_lua_set_activity(lua_State* L);

/**
 * @brief The YYRPC lua binding registration function
 */
void YYRPC_lua_bind(lua_State* L);