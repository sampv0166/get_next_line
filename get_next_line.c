/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:26:16 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/29 22:13:59 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

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

char *ft_strjoin2(char *str1, char *str2)
{
	char *new_string;
	size_t total_len;
	size_t i;
	size_t j;
	
	total_len = ft_strlen(str1) + ft_strlen(str2);
	i = 0;
	j = 0;
	new_string = allocate_memmory(total_len);
	if(new_string == NULL)
		return(NULL);
	
	while(str1 && str1[i]) 
	{
		new_string[i++] = str1[j++];
	}
	j = 0;
	while (str2[j])
	{
		new_string[i++] = str2[j++];
	}	
	
	new_string[i] = '\0';
	free(str1);
	str1 = new_string;
	return (str1);
}

char *get_line(char *saved_line)
{
	char *line;
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	line = allocate_memmory(BUFFER_SIZE);
	if(!line || !saved_line)
	{ 
		free(line);
		return (NULL);
	}
	while(*saved_line && *saved_line != '\n')
	{
		line[i] = saved_line[j];
		j++;
		i++;	
	}
	if(saved_line[j] == '\n')
	{
		line[i] = '\n';
		j++;
	}
	i++;	
	line[i] = '\0';
	free(saved_line);
	saved_line = line;	
	return (saved_line);	
}

char *get_temp_line(int fd , char *saved_line)
{
	int i;
	char buffer[BUFFER_SIZE + 1];
	
	i = 1;
	while (!ft_strchr(buffer, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			return (NULL);
		}
		buffer[i] = '\0';
		if(i != 0)
			saved_line = ft_strjoin2(saved_line,buffer);
	}
	return (saved_line);
}



char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);	
	static char *saved_line;
	char *line;
	size_t k;
		
	k = 0;
	if(!saved_line)
		saved_line = NULL;
	if(!ft_strchr(saved_line,'\n'))	
		  saved_line = get_temp_line(fd,saved_line);
			  
	line = get_line(saved_line);
	
	k = ft_strlen(line);
	saved_line = line + k;

	return (line);
}

