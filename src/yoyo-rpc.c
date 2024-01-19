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

#include <yoyoengine/yoyoengine.h> // ye_logf

#include "yoyo-rpc.h"

// our application context
struct Application app;

// callback function that is effectively useless but necessary
void DISCORD_CALLBACK update_activity_callback(void* data, enum EDiscordResult result)
{
    (void)data; // suppress unused parameter warning
    if (result != DiscordResult_Ok) {
        ye_logf(error,"Error updating Discord activity: %d\n", result);
    }
}

void YYRPC_on_unload()
{
    if(app.core == NULL) return;
    app.core->destroy(app.core);
}

void YYRPC_on_update()
{
    if (app.core != NULL) {
        enum EDiscordResult result = app.core->run_callbacks(app.core);
        if (result != DiscordResult_Ok) {
            ye_logf(error,"Error running Discord callbacks: %d\n", result);
        }
    }
}

bool YYRPC_initialize(DiscordClientId client_id){
    memset(&app, 0, sizeof(app));

    struct IDiscordActivityEvents activities_events;
    memset(&activities_events, 0, sizeof(activities_events));

    struct DiscordCreateParams params;
    DiscordCreateParamsSetDefault(&params);
    params.client_id = client_id;
    params.flags = DiscordCreateFlags_Default;
    params.event_data = &app;
    params.activity_events = &activities_events;

    if (DiscordCreate(DISCORD_VERSION, &params, &app.core) != DiscordResult_Ok) {
        app.core = NULL;
        ye_logf(error, "Failed to initialize Discord RPC\n");
        return false;
    }

    app.activities = app.core->get_activity_manager(app.core);

    ye_logf(info, "Discord RPC initialized through yoyo-rpc\n");

    return true;
}

bool YYRPC_set_activity_complex(struct DiscordActivity activity)
{
    if(app.core == NULL){
        ye_logf(error, "ERROR: Could not set activity because Discord RPC not initialized\n");
        return false;
    }
    app.activities->update_activity(app.activities, &activity, &app, update_activity_callback);
    return true;
}

bool YYRPC_set_activity(char* details, char* state, char* large_image, char* large_text)
{
    if(app.core == NULL){
        ye_logf(error, "ERROR: Could not set activity because Discord RPC not initialized\n");
        return false;
    }
    struct DiscordActivity activity;
    memset(&activity, 0, sizeof(activity));

    sprintf(activity.details, "%s", details);
    sprintf(activity.state, "%s", state);
    sprintf(activity.assets.large_image, "%s", large_image);
    sprintf(activity.assets.large_text, "%s", large_text);

    app.activities->update_activity(app.activities, &activity, &app, update_activity_callback);

    ye_logf(info, "Set activity: %s, %s, %s, %s\n", activity.details, activity.state, activity.assets.large_image, activity.assets.large_text);

    return true;
}

/* Lua */

int YYRPC_lua_initialize(lua_State* L)
{
    DiscordClientId client_id = (DiscordClientId)lua_tointeger(L, 1);
    lua_pushboolean(L, YYRPC_initialize(client_id));
    return 1;
}

int YYRPC_lua_set_activity(lua_State* L)
{
    char* details = (char*)lua_tostring(L, 1);
    char* state = (char*)lua_tostring(L, 2);
    char* large_image = (char*)lua_tostring(L, 3);
    char* large_text = (char*)lua_tostring(L, 4);
    lua_pushboolean(L, YYRPC_set_activity(details, state, large_image, large_text));
    return 1;
}

void YYRPC_lua_bind(lua_State* L)
{
    lua_register(L, "YYRPC_initialize", YYRPC_lua_initialize);
    lua_register(L, "YYRPC_set_activity", YYRPC_lua_set_activity);
}