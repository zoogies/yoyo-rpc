# yoyo-rpc

A plugin (trick) for yoyoengine that wraps the discord games SDK to easily expose control over discord rich presence.

## installation

Installation is extremely simple, just pick ***ONE*** of these two methods:

1. Clone this repository/Download the source code from "releases" and place it in your project's `tricks/` directory
2. Open your project in **yoyoeditor**, locate the "Manage/Install Tricks" button, click "install from git", enter the url to this git repository, and click "Install"

## usage

### From C

At some point, you must call `YYRPC_initialize` and pass it a `DicordClientId` (i64) to construct the context.

From there, you can call `YYRPC_update` to update the presence with some basic keys, or construct a `struct DiscordActivity` and pass it to `YYRPC_set_activity_complex` to utilize the more advanced features of the discord SDK.

The library will automatically run callbacks through yoyoengine every frame for you, and also automatically clean up the context when the game is shutting down.

### From lua

Similarly to the C API, you must call `YYRPC_initialize` (this is from lua now in case that isnt clear) and pass it your client ID as a lua number.

From there, you can call `YYRPC_update` to update the presence with the basic keys. The lua interface does not support the advanced features of the discord SDK, but it should be trivial to port any of the fields exposed to the C api with a proper lua binding.

As with the C API, the library will automatically run callbacks through yoyoengine every frame for you, and also automatically clean up the context when the game is shutting down.

### Explanation of basic keys

Assuming you have already setup your client through the [discord developer portal](https://discord.com/developers/applications) as well as uploaded any media you want to use, you should be ready to go supplying these basic keys to `YYRPC_update`:

- `details` - A **STRING** describing what the player is currently doing.
- `state` - A **STRING** describing the player's current status.
- `large_image` - A **STRING** matching the name of the uploaded image for the large profile artwork.
- `large_text` - A **STRING** describing the large image.

For the lua API, these keys are taken from your arguments in chronological order, and you must supply all of them.