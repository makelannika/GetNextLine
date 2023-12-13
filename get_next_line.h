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

#ifndef BUFFER SIZE
# define BUFFER SIZE 6
#endif

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);

#endif
