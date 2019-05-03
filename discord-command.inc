/*
	Discord Command Processor

	A simple library for discord based commands
	with iZCMD-like code and functionality. Does
	not require any additional libraries. Simple.

	Written by AliLogic
*/

// Include guard

#if defined _discordcmd_included
	#endinput
#endif
#define _discordcmd_included

// Config

#define MAX_CMD_LEN			(50)
#define MAX_CMD_NAME		(10)

// Prefix

#if	!defined CMD_PREFIX
	#define	CMD_PREFIX		'!'
#endif

// Macros

#define DISCORD:%1(%2)		\
	forward discord_%1(%2);	\
	public discord_%1(%2)

#define DC:%1(%2) 			\
	DISCORD:%1(%2)

// Unused code (Can be used later for OnDiscordCMDReceive or OnDiscordCMDPerformed)

#define DISCORD_SUCCESS		(1)
#define DISCORD_FAILURE		(0)

// Code

public DCC_OnChannelMessage(DCC_Channel: channel, DCC_User: author, const message[]) {

	new
		bool: is_bot;

	DCC_IsUserBot(author, is_bot);

	if (!is_bot && message[0] == CMD_PREFIX) { // Skip if the message author is a bot or is not a command

		new // static had issues
			discord[MAX_CMD_LEN] = "discord_",
			pos;

		if ((pos = strfind(message, " ", false, 1)) == -1) { // Space was not found

			strcat(discord, message[1], MAX_CMD_LEN - 8);
			CallLocalFunction(discord, "is", _: channel, "\1");

		} else { // Space was found

			strcat(discord, message[1], pos + 8);

			while (message[pos] == ' ') { // Checks for spaces

				pos ++;
			}

			if (message[pos]) { // Parameter was found

				CallLocalFunction(discord, "is", _: channel, message[pos]);

			} else { // Parameter was not found

				CallLocalFunction(discord, "is", _: channel, "\1");
			}
		}
	}

	return 1;
}