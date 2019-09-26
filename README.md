# discord-command

[![sampctl](https://shields.southcla.ws/badge/sampctl-discord--command-2f2f2f.svg?style=for-the-badge)](https://github.com/AliLogic/discord-command)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->
My own discord command processor alternative, based on iZCMD-like code and functionality.

You need Discord Connector plugin by Maddinat0r and that's all.

#### Version: 0.4.0 (Code Breaking Changes)

## Installation

Simply install to your project:

```bash
sampctl package install AliLogic/discord-command
```

Include in your code and begin using the library:

```pawn
#include <discord-command>
```

## Changes

The command parameters have been changed to `DCC_Message: message_id, params[]` from `DCC_Channel: channel, DCC_User: author, params[])` so you can make use of the functionality that the discord connector plugin provides. This can be useful if you want to use certain parameters, like author, or maybe the message id so you can delete it once its executed.

## Usage

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->
```
DISCORD:stats(DCC_Message: message_id, params[]) {

	new
		DCC_Channel: channel_id,
		DCC_Channel: channel_cmd
	;

	DCC_GetMessageChannel(messageid, channelid);
	channel_cmd = DCC_FindChannelByName("bot-commands");

	if (channel_id != channel_cmd) {
		return 1;
	}

	new
		name[MAX_PLAYER_NAME]
	;

	if (sscanf(params, "s[24]", name))
		return DCC_SendChannelMessage(channel_id, ":warning: You must provide name of the player.");

	// Do something here

	return 1;
}

public OnDiscordCommandPerformed(command[MAX_DCC_CMD_LEN], DCC_Message: message_id, bool: success) {

	new
		DCC_Channel: channel_id
	;
	
	DCC_GetMessageChannel(message_id, channel_id);

	if (!success) {
		return DCC_SendChannelMessage(channel_id, ":x: The command you specified doesn't exist.", "OnDiscordInvalidCommand");
	}

	return 1;
}

forward public OnDiscordInvalidCommand();
public OnDiscordInvalidCommand() {
	new
		DCC_Message: message_id = DCC_GetCreatedMessage
	;
	
	// maybe run a timer to delete it?
	DCC_DeleteMessage(message_id);
}
```
