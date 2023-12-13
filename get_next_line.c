/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:32:38 by amakela           #+#    #+#             */
/*   Updated: 2023/12/13 20:14:19 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

void    *ft_calloc(size_t count, size_t size);
void    ft_bzero(void *s, size_t n);

char	*get_next_line(int fd)
{
	size_t		i;
	char		*temp;
	char		*line;
	size_t		bytes_read;
	static char	*text_read;
	char		buffer[BUFFER_SIZE + 1];

	i = 0;
	if (fd < 0)
		return (NULL);
	if (!text_read)
	{
		text_read = ft_calloc(1, 1);
		if (!text_read)
			return (NULL);
	}
	// read file until a complete line is read or end of line is reached
	while (!ft_strchr(text_read, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		temp = text_read;
		text_read = ft_strjoin(text_read, buffer);
		free(temp);
		if (!text_read)
			return (NULL);
	}
	// get a line from the text read
	while (text_read[i] && text_read[i] != '\n')
		i++;
	if (text_read[i] == '\n')
		i++;
	line = ft_substr(text_read, 0, i);
	if (!line)
		return (NULL);
	// remove line to be returned from the text read
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
	size_t		i;
	char		*str;

	if (n == 0)
		return ;
	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i ++;
	}
}

int main()
{
	fd = open(file, O_RDONLY);

	printf(get_next_line(fd));
	return (0);
}
