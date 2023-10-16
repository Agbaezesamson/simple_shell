#include "shell.h"

/**
 * isCommand - Checks if a file is an executable command.
 * @data: Information about the file.
 * @filePath: The file's path.
 *
 * Return: 1 if it's an executable, 0 otherwise.
 */
int isCommand(info_t *data, char *filePath)
{
	struct stat fileStat;

	(void)data;
	if (!filePath || stat(filePath, &fileStat))
		return (0);

	if (fileStat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateChars - Duplicates characters from a string.
 * @src: The source string.
 * @start: Starting index.
 * @end: Ending index.
 *
 * Return: Pointer to the new buffer.
 */
char *duplicateChars(char *src, int start, int end)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (src[i] != ':')
			buffer[k++] = src[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * findCmdInPath - Finds a command in the PATH string.
 * @data: Information about the command.
 * @pathString: The PATH string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL.
 */
char *findCmdInPath(info_t *data, char *pathString, char *command)
{
	int i = 0, startPos = 0;
	char *fullPath;

	if (!pathString)
		return (NULL);
	if ((_strlen(command) > 2) && startsWith(command, "./"))
	{
		if (isCommand(data, command))
			return (command);
	}
	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			fullPath = duplicateChars(pathString, startPos, i);
			if (!*fullPath)
				_strcat(fullPath, command);
			else
			{
				_strcat(fullPath, "/");
				_strcat(fullPath, command);
			}
			if (isCommand(data, fullPath))
				return (fullPath);
			if (!pathString[i])
				break;
			startPos = i;
		}
		i++;
	}
	return (NULL);
}
