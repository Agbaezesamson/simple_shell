#include "shell.h"

/**
 * get_history_file - prog that gets the path to the history file
 * @info: pointer to the info_t structure
 *
 * Return: pointer to allocated string containing history file path
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - prog that writes the history to a file
 * @info: pointer to the info_t structure
 *
 * Return: 1 if success, -1 for failure
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - prog that reads the history from a file
 * @info: the pointer to the info_t structure
 *
 * Return: the history entries on success, 0 on failure
 */
int read_history(info_t *info)
{
	int q, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (q = 0; q < fsize; q++)
		if (buf[q] == '\n')
		{
			buf[q] = 0;
			build_history_list(info, buf + last, linecount++);
			last = q + 1;
		}
	if (last != q)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - put an entry to the history linked list
 * @info: pointer to the info_t struct
 * @buf: the buffer containing the history entry
 * @linecount: the current line count of the history
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - funct that renumbers the history linked list
 * @info: pointer to the info_t struct
 *
 * Return: new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int q = 0;

	while (node)
	{
		node->num = q++;
		node = node->next;
	}
	return (info->histcount = q);
}
