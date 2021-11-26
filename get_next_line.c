/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:51:23 by jking-ye          #+#    #+#             */
/*   Updated: 2021/11/18 19:09:45 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	count(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

char	*get_next_line_cut(int fd, char *storage)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*tempstr;
	int			i;

	if (storage == NULL)
	{
		storage = malloc(1 * sizeof(char));
		storage[0] = '\0';
	}
	i = read(fd, buffer, BUFFER_SIZE);
	while (i > 0)
	{
		buffer[i] = '\0';
		tempstr = ft_strjoin(storage, buffer);
		free(storage);
		storage = tempstr;
		if (ft_strchr(storage, '\n'))
			break ;
		i = read(fd, buffer, BUFFER_SIZE);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;
	char		*tempstr;
	int			i;

	line = NULL;
	tempstr = get_next_line_cut(fd, storage);
	if (tempstr[0] == '\0')
		free(storage);
	storage = tempstr;
	i = count(storage);
	if (storage[0] != '\0')
	{
		line = ft_substr(storage, 0, (i + 1));
		tempstr = ft_substr(storage, (i + 1), ft_strlen(storage));
		free(storage);
		storage = tempstr;
	}
	if (storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
	}
	return (line);
}
