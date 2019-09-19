/*
	Discord Command Processor

	A simple library for discord based commands.
	Does not require any additional libraries.

	Written by AliLogic
*/

// Include guard

#if defined _discordcmd_included
	#endinput
#endif
#define _discordcmd_included

#tryinclude <discord-connector_new>
#if !defined dcconnector_included
	#error To use this include you need to have "https://github.com/maddinat0r/samp-discord-connector" installed
#endif

// Config

#define MAX_DCC_CMD_LEN		(50)
#define MAX_DCC_CMD_NAME	(10)

// Prefix

#if	!defined CMD_PREFIX
	#define	CMD_PREFIX		'!'
#endif

// Macros

#define DISCORD:%1(%2)		\
	forward discord_%1(%2);	\
	public discord_%1(%2)

#define DCC:%1(%2) 			\
	DISCORD:%1(%2)

// Command result

#define DISCORD_SUCCESS		(1)
#define DISCORD_FAILURE		(0)

// Code
public DCC_OnMessageCreate(DCC_Message: message) {

	new
		DCC_User: message_author,
		bool: is_bot,
		message_content[100];

	DCC_GetMessageAuthor(message, message_author);
	DCC_IsUserBot(message_author, is_bot);
	DCC_GetMessageContent(message, message_content);

	if (!is_bot && message_content[0] == CMD_PREFIX) { // Skip if the message author is a bot or is not a command

		new // static had issues
			discord_cmd[MAX_DCC_CMD_LEN] = "discord_",
			pos;

		if ((pos = strfind(message_content, " ", false, 1)) == -1) { // Space was not found

			strcat(discord_cmd, message_content[1], MAX_DCC_CMD_LEN - 8);

			#if defined OnDiscordCommandPerformed
				OnDiscordCommandPerformed(discord_cmd, message, bool: CallLocalFunction(discord_cmd, "is", _: message, "\1"));
			#else
				CallLocalFunction(discord_cmd, "is", _: message, "\1");
			#endif

		} else { // Space was found

			strcat(discord_cmd, message_content[1], pos + 8);

			while (message_content[pos] == ' ') { // Checks for spaces

				pos ++;
			}

			if (message_content[pos]) { // Parameter was found

				#if defined OnDiscordCommandPerformed
					OnDiscordCommandPerformed(discord_cmd, message, bool: CallLocalFunction(discord_cmd, "is", _: message, message_content[pos]));
				#else
					CallLocalFunction(discord_cmd, "is", _: message, message_content[pos]);
				#endif

			} else { // Parameter was not found

				#if defined OnDiscordCommandPerformed
					OnDiscordCommandPerformed(discord_cmd, message, bool: CallLocalFunction(discord_cmd, "is", _: message, "\1"));
				#else
					CallLocalFunction(discord_cmd, "is", _: message, "\1");
				#endif
			}
		}
	}	
	
	#if defined discdcmd_DCC_OnMessageCreate
		return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
	#else
		return 1;
	#endif
}

// Hooking and functions

#if defined _ALS_DCC_OnMessageCreate
	#undef DCC_OnMessageCreate
#else
	#define _ALS_DCC_OnMessageCreate
#endif

#define DCC_OnMessageCreate discdcmd_DCC_OnMessageCreate
#if defined discdcmd_DCC_OnMessageCreate
	forward discdcmd_DCC_OnMessageCreate(DCC_Message: message);
#endif

#if defined OnDiscordCommandPerformed
	forward OnDiscordCommandPerformed(command[MAX_DCC_CMD_LEN], DCC_Message: message_id, bool: success);
#endif
