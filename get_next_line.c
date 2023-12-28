/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:32:38 by amakela           #+#    #+#             */
/*   Updated: 2023/12/21 19:23:50 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

static ssize_t	read_file(int fd, char **text_read, ssize_t bytes_read);
static char		*get_line(char **text_read, ssize_t bytes_read, char *line);
static int		find_nl(const char *s, int c);
static void		freeptr(char **ptr);

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		bytes_read;
	static char	*text_read;

	line = 0;
	bytes_read = 1;
	if (!text_read)
		text_read = (char *)ft_calloc(1, 1);
	if (!text_read)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		freeptr(&text_read);
		return (NULL);
	}
	bytes_read = read_file(fd, &text_read, bytes_read);
	if (bytes_read == -1)
		return (NULL);
	line = get_line(&text_read, bytes_read, line);
	if (!line || bytes_read == 0)
		freeptr(&text_read);
	if (!line)
		return (NULL);
	return (line);
}

static ssize_t	read_file(int fd, char **text_read, ssize_t bytes_read)
{
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	while (!find_nl(*text_read, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
			break ;
		buffer[bytes_read] = '\0';
		temp = *text_read;
		*text_read = ft_strjoin(*text_read, buffer);
		free(temp);
		if (!*text_read)
		{
			text_read = NULL;
			return (-1);
		}
	}
	if ((bytes_read == -1) || (bytes_read == 0 && **text_read == '\0'))
	{
		freeptr(text_read);
		return (-1);
	}
	return (bytes_read);
}

static char	*get_line(char **text_read, ssize_t bytes_read, char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*text_read)[i] != '\0' && (*text_read)[i] != '\n')
		i++;
	if ((*text_read)[i] == '\n')
		i++;
	line = ft_substr(*text_read, 0, i);
	if (!line)
		return (NULL);
	if (bytes_read == 0)
		return (line);
	temp = *text_read;
	*text_read = ft_substr(*text_read, i, ft_strlen(*text_read) - i);
	free(temp);
	if (!*text_read)
	{
		freeptr(&line);
		text_read = NULL;
		return (NULL);
	}
	return (line);
}

static int	find_nl(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

static void	freeptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
// int main()
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("file.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 	}
// 	return (0);
// }