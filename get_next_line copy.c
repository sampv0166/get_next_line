/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:26:16 by apila-va          #+#    #+#             */
/*   Updated: 2021/11/02 02:53:47 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
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
	new_string = (char *) malloc(sizeof(char) * (total_len + 1));
	if(new_string == NULL)
	{
		free(new_string);
		return(NULL);
	}
	
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

unsigned int get_line_size(char *saved_line)
{
	size_t i;

	i = 0;
	while(saved_line[i] && saved_line[i] != '\n')
	{
		i++;
	}
	if(saved_line[i] == '\n')
		i++;
	return (i);
}

char *get_line(char *saved_line)
{
	char *line;
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	line = (char *) malloc(sizeof(char) * (get_line_size(saved_line)));
	if(line == NULL)
	{ 
		free(line);
		return (NULL);
	}
	while(saved_line[j] && saved_line[j] != '\n')
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
	return (line);	
}

char *get_temp_line(int fd,char *saved_line)
{
	char *buffer;
	int i;
	//char *ptr;

	i = 1;

	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(buffer == NULL)
	{
		free(buffer);
		return(NULL);
	}
	buffer[0] = '\0';

	while(i > 0 && !ft_strchr(saved_line,'\n'))
	{
		i = read(fd,buffer,BUFFER_SIZE);	
		buffer[i] = '\0';
		saved_line =  ft_strjoin2(saved_line,buffer);
	
	}

	if(i <= 0)
	{
		free(buffer);
		if(ft_strlen(saved_line) > 0)
			return (saved_line);
		return(NULL);		
	}
	free(buffer);
	if(saved_line == NULL || !*saved_line)
	{
		free_memmory(&saved_line);
	}
	
	return(saved_line);	
}

char *get_save_line(char *saved_line)
{
	char *new_string;
	size_t len;
	size_t i;

	
	i = 0;

	i = get_line_size(saved_line);
	len = ft_strlen(saved_line + i );
	new_string = (char *)malloc(sizeof(char) * (len));

	if(new_string == NULL|| !saved_line)
	{
		free(new_string);
		return(NULL);
	}
	len = 0;	
	while(saved_line && saved_line[i])
	{
		new_string[len]=saved_line[i];
		i++;
		len++;		
	}
	new_string[len] ='\0';
	free(saved_line);
	saved_line = new_string;
	return(saved_line);
		
}
char *get_next_line(int fd)
{
	static char *saved_line;
	char *next_line;
	if (fd < 0 || fd > 255 || BUFFER_SIZE <= 0)
		return (0);	
	next_line = NULL;
	// if(saved_line == NULL)
	// {
	// 	saved_line = (char *) malloc(sizeof(char) * 1);
	// 	if(saved_line == NULL)
	// 	{
	// 		free(saved_line);
	// 		return(NULL);
	// 	}
	// 	saved_line[0] = '\0';
	// }
	saved_line = get_temp_line(fd ,saved_line);
	if(!saved_line)
	{
		free(next_line);
		free_memmory(&saved_line);
		return(NULL);
	}	
	next_line = get_line(saved_line);
	saved_line = get_save_line(saved_line);
	
	return (next_line);
}

