/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 19:56:12 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/29 05:10:28 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *allocate_memmory(size_t size)
{
	char *memmory;
	
	memmory = (char *)malloc(sizeof(char) * size + 1);
	if(memmory == NULL)
	{
		free(memmory);
		memmory = NULL;
		return (NULL);
	}
	return (memmory);
}

void free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char *ft_strjoin2(char *str1, char *str2)
{
	char *new_string;
	char *start;
	size_t total_len;
	char *str3;
	
	str3 = str1;
	
	total_len = ft_strlen(str1) + ft_strlen(str3);
	
	new_string = allocate_memmory(total_len);
	if(new_string == NULL)
		return(NULL);
	start = new_string;
	
	while(*str3) 
	{
		*new_string = *str3;
		new_string++;
		str3++;
	}
	
	while (*str2)
	{
		*new_string = *str2;
		new_string++;
		str2++;
	}
	
	*new_string = '\0';
	free_memmory(&str1);
	return (start);
}


char	*get_buffer(int fd, char *tmep_line)
{
	int		i;
	char	*buffer;
	char 	*temp;
	
	i = 1;
	buffer = allocate_memmory(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	temp = buffer;
	while (!ft_strchr(buffer, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1 || buffer == NULL || !buffer[0])
		{
			free(buffer);
			buffer = NULL;
			free(tmep_line);
			tmep_line = NULL;
			return (NULL);
		}
		buffer[i] = '\0';
		printf("%s" , buffer);
		tmep_line = ft_strjoin2(tmep_line,buffer);
	}
	free(temp);
	temp = NULL;
	return (tmep_line);
}

char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		printf("first");
		return (0);
	}
	printf("second");
	static char *temp_line;
	char *tmp;
	if(!temp_line)
	{
		temp_line = (char *)malloc(sizeof(char) * 1);
		temp_line[0] = 	'\0';
		tmp = temp_line;
	}
	temp_line = get_buffer(fd, temp_line);
	
	if(temp_line == NULL)
	{
		free_memmory(&tmp);
		return (NULL);
	}
	return (temp_line);
}
