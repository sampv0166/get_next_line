/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:34:08 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/26 21:31:16 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *ft_strjoin2(char *str1, char *str2)
{
	char *joined_string;
	char *ptr;

//	printf("%s\n%s" , str1,str2);
	if(str1 == NULL)
	{
		str1 = malloc(sizeof(char) * 1);
		str1[0] = '\0';
	}
	joined_string = malloc(sizeof(char) *(ft_strlen(str1) + ft_strlen(str2) + 1));
	if(joined_string == NULL)
		return(NULL);
	ptr = joined_string;
	while(*str1)
	{
		*joined_string = *str1;
		joined_string++;
		str1++;
	}
	while (*str2)
	{	
		*joined_string = *str2;
		joined_string++;
		str2++;
	}
	*joined_string = '\0';
//	free(str1);
	return (ptr);
}

char *get_temp_line(int fd, char *line_to_join)
{
	char *temp_line;
	size_t i;

	i = 1;
	temp_line = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (temp_line == NULL)
	{
		free(temp_line);
		return (NULL);
	}
	
	while (!ft_strchr(temp_line,'\n') && i != 0)
	{	
		i = read(fd,temp_line,BUFFER_SIZE);
		if(i == -1)
		{
			free(temp_line);
			return (NULL);
		}
		temp_line[i] = '\0';
	//	printf("%s",temp_line);
		line_to_join = ft_strjoin2(line_to_join,temp_line);
	}
	//printf("%s",line_to_join);
	free (temp_line);
	return (line_to_join);
}

char *get_line(char *line_start)
{
	size_t i ;
	char *line;
	
	i = 0;

	while(line_start[i] && line_start[i] != '\n')
	{
		i++;
	}
	line = malloc(sizeof(char) * i + 1);
	if(line == NULL)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while(line_start[i] && line_start[i] != '\n')
	{
		line[i] = line_start[i];
		i++;
	}
	return(line);
}

char *save(char *line_start)
{
	size_t i;
	size_t j;
	char *line;

	i = 0;
	while(line_start[i] && line_start[i] != '\n')
	{
	//	printf("%c",line_start[i]);
		i++;
	}
	i++;
	j = 0;
	while(line_start[i + j])
	{
		j++;
	}
	line = malloc(sizeof(char) * j + 1);
	if(line == NULL)
	{
		free(line);
		return (NULL);
	}
	j = 0;
	while(line_start[i])
	{
		line[j] = line_start[i];	
		i++;
		j++;
	}
	line[j] = '\0';
	return (line);
}

char *get_next_line(int fd)
{
	char static *line_start;
	char *line;
	size_t i;

	i = 0;
	line_start = get_temp_line(fd, line_start);
	line = get_line(line_start);
	line_start = save(line_start);
	printf("next line :%s\n" , line);
//	printf("saved line :%s\n" , line_start);
	return (line_start);
}

int main ()
{
        int fd ;
        size_t i;
        char buf[1];
        fd = open ("./file.txt" , O_RDONLY);
//      i = read(fd,buf,1);
//      printf("%s",buf);
        get_next_line(fd);
        get_next_line(fd);
        get_next_line(fd);
  		//printf("%s",get_next_line(fd));
        return (0);
}
