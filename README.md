# discord-command

My own discord command processor alternative, based on iZCMD-like code and functionality.

You need Discord Connector plugin by Maddinat0r and that's all.

## Examples

```DISCORD:stats(DCC_Channel: channel, params[]) {

	if (channel != gCommandChannel) {
		return 1;
	}

	new
		name[MAX_PLAYER_NAME];

	if (sscanf(params, "s[24]", name))
		return DCC_SendChannelMessage(channel, ":warning: You must provide a name of the player.");

	// Do something here

	return 1;
}

DISCORD:tick(DCC_Channel: channel) {

	if (channel != gCommandChannel) {
		return 1;
	}

	new
		string[50];

	format(string, sizeof string, ":stopwatch: Tick: %i", GetServerTickRate());
	DCC_SendChannelMessage(channel, string);

	return 1;
}```
