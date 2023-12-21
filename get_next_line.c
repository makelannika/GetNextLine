/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:32:38 by amakela           #+#    #+#             */
/*   Updated: 2023/12/21 12:47:05 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	size_t		i;
	char		*temp;
	char		*line;
	size_t		bytes_read;
	static char	*text_read;
	char		buffer[BUFFER_SIZE + 1];

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!text_read)
	{
		text_read = (char *)ft_calloc(1, 1);
		if (!text_read)
			return (NULL);
	}
	while ((!ft_strchr(text_read, '\n')) && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		temp = text_read;
		text_read = ft_strjoin(text_read, buffer);
		free(temp);
		if (!text_read)
			return (NULL);
	}
	if (bytes_read < 0)
	{
		free(text_read);
		return (NULL);
	}
	while (text_read[i] && text_read[i] != '\n')
		i++;
	if (text_read[i] == '\n')
		i++;
	line = ft_substr(text_read, 0, i);
	if (!line || bytes_read == 0)
	{
		free(text_read);
		if (!ft_strlen(line))
			return (NULL);
		return (line);
	}
	temp = text_read;
	text_read = ft_substr(text_read, i, ft_strlen(text_read) - i);
	free(temp);
	if (!text_read)
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
/*
int main()
{
	int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
	}
	return (0);
}*/
