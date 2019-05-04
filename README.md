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

## Installation

Simply install to your project:

```bash
sampctl package install infin1tyy/discord-command
```

Include in your code and begin using the library:

```pawn
#include <discord-command>
```

## Usage

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->
```
DISCORD:stats(DCC_Channel: channel, DCC_User: author, params[]) {

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

DISCORD:tick(DCC_Channel: channel, DCC_User: author) {

	if (channel != gCommandChannel) {
		return 1;
	}

	new
		string[50];

	format(string, sizeof string, ":stopwatch: Tick: %i", GetServerTickRate());
	DCC_SendChannelMessage(channel, string);

	return 1;
}
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
