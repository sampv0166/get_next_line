/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:26:16 by apila-va          #+#    #+#             */
/*   Updated: 2021/11/07 01:43:14 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin(char **saved_line, char *buffer)
{
	char	*new_string;
	int		total_len;
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = *saved_line;
	i = 0;
	j = 0;
	total_len = ft_strlen(*saved_line) + ft_strlen(buffer) + 1;
	new_string = (char *) malloc(sizeof(char) * (total_len));
	if (new_string == NULL)
		return (NULL);
	while (*ptr)
	{
		new_string[i++] = *ptr;
		ptr++;
	}
	j = 0;
	while (buffer[j])
		new_string[i++] = buffer[j++];
	new_string[i] = '\0';
	free_memmory(saved_line);
	return (new_string);
}

static char	*save_the_rest(char **saved_line)
{
	char	*new_string;
	size_t	length_of_save;
	size_t	i;

	new_string = NULL;
	i = get_current_line_size(*saved_line);
	length_of_save = ft_strlen(*saved_line + i);
	if (length_of_save > 0)
	{
		new_string = (char *)malloc(sizeof(char) * (length_of_save + 1));
		if (new_string == NULL)
			return (NULL);
		length_of_save = 0;
		while (*(*saved_line + i))
		{
			new_string[length_of_save] = *(*saved_line + i);
			i++;
			length_of_save++;
		}
		new_string[length_of_save] = '\0';
		free_memmory(&*saved_line);
		return (new_string);
	}
	free_memmory(&*saved_line);
	return (new_string);
}

static char	*get_current_line(char **saved_line)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc(sizeof(char) * (get_current_line_size(*saved_line) + 1));
	if (!line)
		return (NULL);
	while (*(*saved_line + j) && *(*saved_line + j) != '\n')
		line[i++] = *(*saved_line + j++);
	if (*(*saved_line + j) == '\n')
	{
		line[i++] = '\n';
		j++;
	}
	line[i++] = '\0';
	return (line);
}

static char	*get_temp_line(int fd, char **saved_line, int read_return)
{
	char	*buffer;

	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	while (read_return > 0 && ft_strchr(*saved_line, '\n') == NULL)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return <= 0)
			break ;
		buffer[read_return] = '\0';
		*saved_line = ft_strjoin(saved_line, buffer);
	}
	free(buffer);
	return (*saved_line);
}

char	*get_next_line(int fd)
{
	static char		*saved_line[1024];
	char			*next_line;

	if (!saved_line[fd])
	{
		saved_line[fd] = (char *) malloc(sizeof(char) * 1);
		*saved_line[fd] = '\0';
		if (saved_line[fd] == NULL)
			return (NULL);
	}
	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_memmory(&saved_line[fd]));
	saved_line[fd] = get_temp_line(fd, &saved_line[fd], 1);
	if (!saved_line[fd] || saved_line[fd][0] == '\0')
		return (free_memmory(&saved_line[fd]));
	next_line = get_current_line(&saved_line[fd]);
	saved_line[fd] = save_the_rest(&saved_line[fd]);
	return (next_line);
}
