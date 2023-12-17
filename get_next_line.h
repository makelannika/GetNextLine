/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:34:14 by amakela           #+#    #+#             */
/*   Updated: 2023/12/04 12:26:31 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
char    *ft_strchr(const char *s, int c);
void    *ft_calloc(size_t count, size_t size);
void    ft_bzero(void *s, size_t n);
size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s1);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strjoin(char const *s1, char const *s2);

#endif
