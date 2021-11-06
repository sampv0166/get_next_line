/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:43:37 by apila-va          #+#    #+#             */
/*   Updated: 2021/11/05 17:32:20 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	get_current_line_size(char *saved_line)
{
	size_t	i;

	i = 0;
	while (saved_line[i] && saved_line[i] != '\n')
	{
		i++;
	}
	if (saved_line[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (0);
}

char	*free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}