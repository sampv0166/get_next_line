/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lineLAST.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:26:16 by apila-va          #+#    #+#             */
/*   Updated: 2021/11/01 10:54:35 by apila-va         ###   ########.fr       */
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
	
	memmory = (char *)malloc(sizeof(char) * size );
	if(memmory == NULL)
	{
		free_memmory(&memmory);
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
	new_string = allocate_memmory(total_len + 1);
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
	free_memmory(&str1);
	return (new_string);
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
	line = allocate_memmory(get_line_size(saved_line));
	if(!line || !saved_line)
	{
		free_memmory(&line);
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



char *get_buffer(int fd,char *buffer,char *saved_line)
{
	int i;
	char *read_buffer;
	read_buffer = allocate_memmory(BUFFER_SIZE + 1);
	if(read_buffer == NULL)
		return(NULL);
	
	i = read(fd,read_buffer,BUFFER_SIZE);
	if(i <= 0)
	{
		//read_buffer[i] = '\0';
		free_memmory(&buffer);
		free_memmory(&read_buffer);
		saved_line  = NULL;
		return(saved_line);
	}
	else
	{	
		read_buffer[i] = '\0';
		free_memmory(&buffer);
		buffer = read_buffer;
		return(buffer);	
	}
}

char *get_save_line(char *saved_line)
{
	char *new_string;
	size_t len;
	size_t i;
	
	i = 0;
	while(saved_line[i] && saved_line[i] != '\n')
	{
		i++;
	}
	if(saved_line[i] == '\n')
		i++;
		
	len = ft_strlen(saved_line + i);
	new_string = allocate_memmory(len + 1);
	if(!new_string)
		return(NULL);
	len = 0;	
	while(saved_line[i])
	{
		new_string[len]=saved_line[i];
		i++;
		len++;		
	}
	new_string[len] ='\0';
	free_memmory(&saved_line);
	saved_line = new_string;
	return(saved_line);		
}

char *get_temp_line(int fd,char *saved_line)
{
	int i;
	char *buffer;

	i = 1;
	buffer = allocate_memmory(BUFFER_SIZE + 1);
	if(!buffer)
		return (NULL);
	while(!ft_strchr(saved_line,'\n'))
	{
		i  = read(fd,buffer,BUFFER_SIZE);
		if(i == -1)
		{
			break;
		}
		if(i == 0)
		{
			free_memmory(&buffer);
			return (saved_line);
		}
		saved_line = ft_strjoin2(saved_line,buffer);		
	}
	free_memmory(&buffer);
	return(saved_line);		
}

char *get_next_line(int fd)
{	
	static char *saved_line;
	char *next_line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);

	saved_line = get_temp_line(fd,saved_line);
	if(!saved_line)
	{	
		free_memmory(&saved_line);
		return(NULL);
	}
	next_line = get_line(saved_line);
	saved_line = get_save_line(saved_line);	
	//free_memmory(&buffer);
	return (next_line);
}

