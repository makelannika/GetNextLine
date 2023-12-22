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

static ssize_t  read_file(int fd, char **text_read);
static char		*get_line(char **text_read, ssize_t bytes_read);

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char *text_read;
	char        buffer[BUFFER_SIZE + 1];
	
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!text_read)
	{
		text_read = (char *)ft_calloc(1, 1);
		if (!text_read)
			return (NULL);
	}
	bytes_read = read_file(fd, &text_read);
	if (bytes_read == -1)
		return (NULL);
	return (get_line(&text_read, bytes_read));
}

static ssize_t	read_file(int fd, char **text_read)
{
	char	*temp;
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE + 1];

	while ((!ft_strchr(*text_read, '\n')) && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		temp = *text_read;
		*text_read = ft_strjoin(*text_read, buffer);
		free(temp);
		if (!*text_read)
			return(-1);
	}
	if (bytes_read == -1)
	{
		free(*text_read);
		return (-1);
	}
	return(bytes_read);
}

static char	*get_line(char **text_read, ssize_t bytes_read)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*text_read)[i] != '\0' && (*text_read)[i] != '\n')
		i++;
	if ((*text_read)[i] == '\n')
		i++;
	line = ft_substr(*text_read, 0, i);
	if (!line || bytes_read == 0)
	{
		free(*text_read);
		if (!line)
			return (NULL);
		return (line);
	}
	temp = *text_read;
	*text_read = ft_substr(*text_read, i, ft_strlen(*text_read) - i);
	free(temp);
	if (!*text_read)
		return (NULL);
	return (line);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	ptr = malloc (count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*((char *)s + n - 1) = 0;
		n--;
	}
	return ;
}

char	*ft_strchr(const char *s, int c)
{
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s);
	while (i <= length)
		if (s[i] != c)
			i++;
	else
		return ((char *)&s[i]);
	return (0);
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